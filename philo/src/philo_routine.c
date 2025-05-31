/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:18:45 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 16:34:29 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
}

static void	eat(t_philo *philo)
{
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	philo->meals_eaten++;
	usleep(philo->arg->time_to_eat * 1000);
}

static void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	sleep_philo(t_philo *philo)
{
	print_state(philo, "is sleeping");
	usleep(philo->arg->time_to_sleep * 1000);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&philo->arg->simulation_mutex);
		if (philo->arg->simulation_finished)
		{
			pthread_mutex_unlock(&philo->arg->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->arg->simulation_mutex);
		print_state(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
