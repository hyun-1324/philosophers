/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:23:24 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 11:59:34 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_arg	*arg_struct;
	int		i;

	philos = (t_philo *)arg;
	arg_struct = philos[0].arg;
	while (!arg_struct->simulation_finished)
	{
		i = 0;
		while (i < arg_struct->number_of_philos)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			if (get_current_time() - philos[i].last_meal_time > arg_struct->time_to_die)
			{
				print_state(&philos[i], "died");
				arg_struct->simulation_finished = 1;
				pthread_mutex_unlock(&philos[i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].meal_mutex);\
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
