/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:23:24 by donheo            #+#    #+#             */
/*   Updated: 2025/06/06 00:15:50 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_if_all_eaten(t_philo *philos, t_args *args)
{
	int	i;
	int	meals_to_eat;

	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		meals_to_eat = args->number_must_eat - philos[i].meals_eaten;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		if (meals_to_eat > 0)
		{
			return (0);
		}
		i++;
	}
	args->simulation_finished = 1;
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
	sleep_time(philo->args, philo->args->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
