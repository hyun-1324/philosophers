/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:06:28 by donheo            #+#    #+#             */
/*   Updated: 2025/06/08 19:23:52 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_args(t_args *args, int argc, char **argv, int i)
{
	if (!is_str_valid_number(argc, argv))
		return (0);
	if (!check_overflow_and_save_args(args, argc, argv, 0))
		return (0);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->philo_num);
	if (!args->forks)
		return (print_error("failed to allocate memory for forks"), 0);
	while (i < args->philo_num)
	{
		if (pthread_mutex_init(&args->forks[i++], NULL))
		{
			destroy_fork_mutexes(args, i - 1);
			free(args->forks);
			print_error("failed to initialize fork mutex");
			return (0);
		}
	}
	if (pthread_mutex_init(&args->print_mutex, NULL))
	{
		destroy_fork_mutexes(args, i - 1);
		free(args->forks);
		print_error("failed to initialize print mutex");
		return (0);
	}
	return (1);
}

static int	init_philos(t_philo **philos, t_args *args, int i)
{
	*philos = malloc(sizeof(t_philo) * args->philo_num);
	if (!*philos)
		return (cleanup_on_philo_failure(args), 0);
	while (i < args->philo_num)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].args = args;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = get_current_time();
		if ((i + 1) % 2 == 0)
		{
			(*philos)[i].left_fork = &args->forks[(i + 1) % args->philo_num];
			(*philos)[i].right_fork = &args->forks[i];
		}
		else
		{
			(*philos)[i].right_fork = &args->forks[(i + 1) % args->philo_num];
			(*philos)[i].left_fork = &args->forks[i];
		}
		if (pthread_mutex_init(&(*philos)[i].meal_mutex, NULL))
			return (cleanup_on_meal_failure(args, *philos, i), 0);
		i++;
	}
	return (1);
}

static int	start_philo_threads(t_args *args, t_philo *philos, int i)
{
	args->start_time = get_current_time();
	if (args->philo_num == 1)
	{
		if ((pthread_create(&philos[i].thread, NULL, \
handle_single_philo, &philos[i])) != 0)
		{
			cleanup_on_thread_failure(args, philos, i);
			return (0);
		}
	}
	else
	{
		while (i < args->philo_num)
		{
			if ((pthread_create(&philos[i].thread, NULL, \
philo_routine, &philos[i])) != 0)
			{
				cleanup_on_thread_failure(args, philos, i);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

static void	monitor_philo(t_philo *philos, t_args *args)
{
	int		i;
	long	last_meal;

	while (1)
	{
		i = 0;
		while (i < args->philo_num)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			last_meal = philos[i].last_meal_time;
			pthread_mutex_unlock(&philos[i].meal_mutex);
			if (get_current_time() - last_meal > args->time_to_die)
			{
				args->simulation_finished = 1;
				args->died_philo = philos[i].id;
				return ;
			}
			i++;
		}
		if (args->number_must_eat > 0 && finish_if_all_eaten(philos, args))
			return ;
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
		return (print_error("invalid argument number"), EXIT_FAILURE);
	memset(&args, 0, sizeof(t_args));
	if (!init_args(&args, argc, argv, 0))
		return (EXIT_FAILURE);
	if (!init_philos(&philos, &args, 0))
		return (EXIT_FAILURE);
	if (!start_philo_threads(&args, philos, 0))
		return (EXIT_FAILURE);
	monitor_philo(philos, &args);
	print_died_philo(&args);
	cleanup_resources(&args, philos);
	return (EXIT_SUCCESS);
}
