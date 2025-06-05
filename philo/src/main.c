/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:06:28 by donheo            #+#    #+#             */
/*   Updated: 2025/06/06 00:16:41 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args(t_args *args, int argc, char **argv)
{
	int	i;

	is_str_valid_number(argc, argv);
	check_overflow_and_save_arg(args, argc, argv, 0);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->num_of_philo);
	if (!args->forks)
		exit_with_error("failed memory allocation for forks");
	i = 0;
	while (i < args->num_of_philo)
		pthread_mutex_init(&args->forks[i++], NULL);
	pthread_mutex_init(&args->print_mutex, NULL);
}

static void	init_philo(t_philo **philo, t_args *args)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * args->num_of_philo);
	if (!*philo)
		return (free(args->forks), \
	exit_with_error("failed memory allocation for philo"));
	i = 0;
	while (i < args->num_of_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].args = args;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].last_meal_time = get_current_time();
		if ((i + 1) % 2 == 0)
		{
			(*philo)[i].left_fork = &args->forks[(i + 1) % args->num_of_philo];
			(*philo)[i].right_fork = &args->forks[i];
		}
		else
		{
			(*philo)[i].right_fork = &args->forks[(i + 1) % args->num_of_philo];
			(*philo)[i].left_fork = &args->forks[i];
		}
		pthread_mutex_init(&(*philo)[i++].meal_mutex, NULL);
	}
}

static void	start_philo(t_args *args, t_philo *philo, int i)
{
	args->start_time = get_current_time();
	i = 0;
	if (args->num_of_philo == 1)
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
		while (i < args->num_of_philo)
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
	long	last_meal;

	while (1)
	{
		i = 0;
		while (i < args->num_of_philo)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			last_meal = philo[i].last_meal_time;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			if (get_current_time() - last_meal > args->time_to_die)
			{
				args->simulation_finished = 1;
				args->died_philo = philo[i].id;
				return ;
			}
			i++;
		}
		if (args->number_must_eat > 0 && finish_if_all_eaten(philo, args))
			return ;
		usleep(1000);
	}
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
	start_philo(&args, philo, 0);
	monitor_philo(philo, &args);
	print_died_philo(&args);
	i = 0;
	while (i < args.num_of_philo)
		pthread_join(philo[i++].thread, NULL);
	cleanup_resources(&args, philo);
	return (0);
}
