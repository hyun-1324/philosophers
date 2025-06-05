/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:15:32 by donheo            #+#    #+#             */
/*   Updated: 2025/06/06 00:15:19 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_on_create_failure(t_args *args, t_philo *philo, \
int created_threads)
{
	int	i;

	i = 0;
	args->simulation_finished = 1;
	while (i < created_threads)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&args->print_mutex);
	free(args->forks);
	free(philo);
}

void	cleanup_resources(t_args *args, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&args->print_mutex);
	free(args->forks);
	free(philo);
}
