/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:23:24 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 21:04:35 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_if_all_eaten(t_philo *philos, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philos)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[i].meals_eaten < arg->number_must_eat)
		{
			pthread_mutex_unlock(&philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_lock(&arg->simulation_mutex);
	arg->simulation_finished = 1;
	pthread_mutex_unlock(&arg->simulation_mutex);
	return (1);
}

int	handle_single_philo(t_philo *philo)
{
	if (philo->arg->number_of_philos == 1)
	{
		print_state(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		usleep(philo->arg->time_to_die * 1000);
		return (1);
	}
	return (0);
}
