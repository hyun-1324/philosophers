/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:23:24 by donheo            #+#    #+#             */
/*   Updated: 2025/06/05 11:51:52 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_if_all_eaten(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[i].meals_eaten < args->number_must_eat)
		{
			pthread_mutex_unlock(&philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_lock(&args->simulation_mutex);
	args->simulation_finished = 1;
	pthread_mutex_unlock(&args->simulation_mutex);
	args->all_eaten = 1;
	return (1);
}

void	*handle_single_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	print_state(philo, "is thinking");
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	usleep(philo->args->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
