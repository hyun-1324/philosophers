/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:06:28 by donheo            #+#    #+#             */
/*   Updated: 2025/06/03 15:12:37 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args(t_args *arg, int argc, char **argv)
{
	int	i;

	is_str_valid_number(argc, argv);
	check_overflow_and_save_arg(arg, argc, argv, 0);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->number_of_philos);
	if (!arg->forks)
		exit_with_error("failed memory allocation for forks");
	i = 0;
	while (i < arg->number_of_philos)
		pthread_mutex_init(&arg->forks[i++], NULL);
	pthread_mutex_init(&arg->print_mutex, NULL);
	pthread_mutex_init(&arg->simulation_mutex, NULL);
	arg->simulation_finished = 0;
}

static void	init_philo(t_philo **philo, t_args *args)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * args->number_of_philos);
	if (!*philo)
	{
		free(args->forks);
		exit_with_error("failed memory allocation for philo");
	}
	i = 0;
	while (i < args->number_of_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].args = args;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].last_meal_time = get_current_time() - args->start_time;
		(*philo)[i].left_fork = &args->forks[i];
		(*philo)[i].right_fork = &args->forks[(i + 1) % args->number_of_philos];
		pthread_mutex_init(&(*philo)[i].meal_mutex, NULL);
		i++;
	}
}

static void	start_philo(t_args *args, t_philo *philo)
{
	int	i;

	args->start_time = get_current_time();
	i = 0;
	if (args->number_of_philos == 1)
	{
		if ((pthread_create(&philo[i].thread, NULL, \
			handle_single_philo, &philo[i])) != 0)
		{
			cleanup_on_create_failure(args, philo, i);
			exit_with_error("failed to create philo thread");
		}
	}
	else
	{
		while (i < args->number_of_philos)
		{
		if ((pthread_create(&philo[i].thread, NULL, \
			philo_routine, &philo[i])) != 0)
		{
			cleanup_on_create_failure(args, philo, i);
			exit_with_error("failed to create philo thread");
		}
		i++;
		}
	}
}

static void	monitor_philo(t_philo *philo, t_args *args)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < args->number_of_philos)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			if (get_current_time() - philo[i].last_meal_time > args->time_to_die)
			{
				pthread_mutex_unlock(&philo[i].meal_mutex);
				pthread_mutex_lock(&args->simulation_mutex);
				args->simulation_finished = 1;
				pthread_mutex_unlock(&args->simulation_mutex);
				print_state(&philo[i], "died");
				return ;
			}
			pthread_mutex_unlock(&philo[i++].meal_mutex);
		}
		if (args->number_must_eat > 0 && finish_if_all_eaten(philo, args))
			return ;
		usleep(500);
	}
	usleep(1000);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philo;
	int		i;

	if (argc != 5 && argc != 6)
		exit_with_error("invalid argument number");
	memset(&args, 0, sizeof(t_args));
	init_args(&args, argc, argv);
	init_philo(&philo, &args);
	start_philo(&args, philo);
	monitor_philo(philo, &args);
	i = 0;
	while (i < args.number_of_philos)
		pthread_join(philo[i++].thread, NULL);
	cleanup_resources(&args, philo);
	return (0);
}
