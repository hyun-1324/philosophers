/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:23:29 by donheo            #+#    #+#             */
/*   Updated: 2025/06/06 00:05:50 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_time(t_args *args, long sleep_time)
{
	long	current_time;
	long	time_to_wait;
	long	sleep_chunk;

	current_time = get_current_time();
	while (current_time < sleep_time)
	{
		if (args->simulation_finished)
			break ;
		time_to_wait = (sleep_time - current_time) * 1000;
		if (time_to_wait <= 0)
			break ;
		if (time_to_wait > 250)
			sleep_chunk = 250;
		else
			sleep_chunk = time_to_wait;
		usleep(sleep_chunk);
		current_time = get_current_time();
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating");
	sleep_time(philo->args, get_current_time() + philo->args->time_to_eat);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_philo(t_philo *philo)
{
	print_state(philo, "is sleeping");
	sleep_time(philo->args, get_current_time() + philo->args->time_to_sleep);
}
