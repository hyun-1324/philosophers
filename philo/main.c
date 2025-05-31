/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:06:28 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 11:17:22 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_err_and_exit(char *error_message)
{
	printf("%s\n", error_message);
	exit(EXIT_FAILURE);
}

static void	init_arg(t_arg *arg, int argc, char **argv)
{
	int	i;

	arg->number_of_philos = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->number_must_eat = -1;
	if (argc == 6)
		arg->number_must_eat = ft_atoi(argv[5]);
	if (arg->number_of_philos <= 0 || arg->time_to_die <= 0 || \
		arg->time_to_eat <= 0 || arg->time_to_sleep <= 0 || \
		(argc == 6 && arg->number_must_eat <= 0))
		print_err_and_exit("argument values must be positive integers");
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->number_of_philos);
	if (!arg->forks)
		print_err_and_exit("failed memory allocation for forks");
	i = 0;
	while (i < arg->number_of_philos)
		pthread_mutex_init(&arg->forks[i++], NULL);
	pthread_mutex_init(&arg->print_mutex, NULL);
	arg->simulation_finished = 0;
}

static void	init_philo(t_philo **philo, t_arg *arg)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * arg->number_of_philos);
	if (!philo)
	{
		free(arg->forks);
		print_err_and_exit("failed memory allocation for philo");
	}
	i = 0;
	while (i < arg->number_of_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].arg = arg;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].last_meal_time = current_timestamp(arg->start_time);
		(*philo)[i].left_fork = &arg->forks[i];
		(*philo)[i].right_fork = &arg->forks[(i + 1) % arg->number_of_philos];
		pthread_mutex_init(&(*philo)[i].meal_mutex, NULL);
		i++;
	}
}

static void	start_philo(t_arg *arg, t_philo *philo)
{
	int	i;
	pthread_t	monitor_thread;

	arg->start_time = get_current_time();
	i = 0;
	while (i < arg->number_of_philos)
	{
		if ((pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i])) != 0)
		{
			cleanup_on_create_failure(arg, philo, i);
			print_err_and_exit("failed to create philo thread");
		}
		i++;
	}
	if ((pthread_create(&monitor_thread, NULL, monitor_routine, philo)) != 0)
	{
		cleanup_on_create_failure(arg, philo, arg->number_of_philos);
		print_err_and_exit("failed to create monitor thread");
	}
	i = 0;
	while (i < arg->number_of_philos)
		pthread_join(philo[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
}

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_philo	*philo;

	if (argc !=5 && argc != 6)
		print_err_and_exit("invalid argument number");
	memset(&arg, 0, sizeof(t_arg));
	init_arg(&arg, argc, argv);
	init_philo(&philo, &arg);
	start_philo(&arg, philo);
	cleanup_resources(&arg, philo);
	return (0);
}
