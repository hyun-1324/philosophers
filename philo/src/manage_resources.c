/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:15:32 by donheo            #+#    #+#             */
/*   Updated: 2025/06/08 19:25:09 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_fork_mutexes(t_args *args, int fork_count)
{
	int	i;

	i = 0;
	while (i < fork_count)
		pthread_mutex_destroy(&args->forks[i]);
}

void	cleanup_on_philo_failure(t_args *args)
{
	destroy_fork_mutexes(args, args->philo_num);
	pthread_mutex_destroy(&args->print_mutex);
	free(args->forks);
	print_error("failed to allocate memory for philos");
}

void	cleanup_on_meal_failure(t_args *args, t_philo *philos, \
int meal_count)
{
	int	i;

	i = 0;
	while (i < args->philo_num)
	{
		pthread_mutex_destroy(&args->forks[i]);
		if (i < meal_count)
		{
			pthread_mutex_destroy(&philos[i].meal_mutex);
		}
		i++;
	}
	free(philos);
	free(args->forks);
	print_error("failed to initialize meal mutex");
}

void	cleanup_on_thread_failure(t_args *args, t_philo *philos, \
int thread_count)
{
	int	i;

	i = 0;
	args->simulation_finished = 1;
	while (i < thread_count)
		pthread_join(philos[i++].thread, NULL);
	i = 0;
	while (i < args->philo_num)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&args->print_mutex);
	free(args->forks);
	free(philos);
	print_error("failed to create philos thread");
}

void	cleanup_resources(t_args *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->philo_num)
		pthread_join(philos[i++].thread, NULL);
	i = 0;
	while (i < args->philo_num)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&args->print_mutex);
	free(args->forks);
	free(philos);
}
