/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:15:32 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 11:06:26 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_on_create_failure(t_arg *arg, t_philo *philo, int created_threads)
{
	int	i;

	i = 0;
	while (i < created_threads)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	while (i < arg->number_of_philos)
	{
		pthread_mutex_destroy(&arg->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&arg->print_mutex);
	free(arg->forks);
	free(philo);
}

void	cleanup_resources(t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philos)
	{
		pthread_mutex_destroy(&arg->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&arg->print_mutex);
	free(arg->forks);
	free(philo);
}
