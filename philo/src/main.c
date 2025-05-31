/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:06:28 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 21:40:15 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_arg(t_arg *arg, int argc, char **argv)
{
	int	i;

	is_str_valid_number(argc, argv);
	check_overflow_and_save_arg(arg, argc, argv, 0);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->number_of_philos);
	if (!arg->forks)
		print_err_and_exit("failed memory allocation for forks");
	i = 0;
	while (i < arg->number_of_philos)
		pthread_mutex_init(&arg->forks[i++], NULL);
	pthread_mutex_init(&arg->print_mutex, NULL);
	pthread_mutex_init(&arg->simulation_mutex, NULL);
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
		(*philo)[i].last_meal_time = get_current_time() - arg->start_time;
		(*philo)[i].left_fork = &arg->forks[i];
		(*philo)[i].right_fork = &arg->forks[(i + 1) % arg->number_of_philos];
		pthread_mutex_init(&(*philo)[i].meal_mutex, NULL);
		i++;
	}
}

static void	start_philo(t_arg *arg, t_philo *philo)
{
	int	i;

	arg->start_time = get_current_time();
	i = 0;
	while (i < arg->number_of_philos)
	{
		if ((pthread_create(&philo[i].thread, NULL, \
			philo_routine, &philo[i])) != 0)
		{
			cleanup_on_create_failure(arg, philo, i);
			print_err_and_exit("failed to create philo thread");
		}
		i++;
	}
}

static void	monitor_philo(t_philo *philo, t_arg *arg)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < arg->number_of_philos)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			if (get_current_time() - philo[i].last_meal_time > arg->time_to_die)
			{
				pthread_mutex_unlock(&philo[i].meal_mutex);
				pthread_mutex_lock(&arg->simulation_mutex);
				arg->simulation_finished = 1;
				pthread_mutex_unlock(&arg->simulation_mutex);
				print_state(&philo[i], "died");
				return ;
			}
			pthread_mutex_unlock(&philo[i++].meal_mutex);
		}
		if (arg->number_must_eat > 0 && finish_if_all_eaten(philo, arg))
			return ;
	}
}

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_philo	*philo;
	int		i;

	if (argc != 5 && argc != 6)
		print_err_and_exit("invalid argument number");
	memset(&arg, 0, sizeof(t_arg));
	init_arg(&arg, argc, argv);
	init_philo(&philo, &arg);
	start_philo(&arg, philo);
	monitor_philo(philo, &arg);
	i = 0;
	while (i < arg.number_of_philos)
		pthread_join(philo[i++].thread, NULL);
	cleanup_resources(&arg, philo);
	return (0);
}
