/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:23:29 by donheo            #+#    #+#             */
/*   Updated: 2025/06/06 01:16:18 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_until(t_args *args, long target_time_ms)
{
	long	current_time_ms;
	long	time_to_wait_us;
	long	sleep_interval_us;

	current_time_ms = get_current_time();
	while (current_time_ms < target_time_ms)
	{
		if (args->simulation_finished)
			break ;
		time_to_wait_us = (target_time_ms - current_time_ms) * 1000;
		if (time_to_wait_us <= 0)
			break ;
		if (time_to_wait_us > 250)
			sleep_interval_us = 250;
		else
			sleep_interval_us = time_to_wait_us;
		usleep(sleep_interval_us);
		current_time_ms = get_current_time();
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
	sleep_until(philo->args, get_current_time() + philo->args->time_to_eat);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_philo(t_philo *philo)
{
	print_state(philo, "is sleeping");
	sleep_until(philo->args, get_current_time() + philo->args->time_to_sleep);
}
