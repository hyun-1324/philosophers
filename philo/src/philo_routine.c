/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:18:45 by donheo            #+#    #+#             */
/*   Updated: 2025/06/05 16:52:30 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_even_number_philos(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		print_state(philo, "is thinking");
		take_forks(philo, philo->id);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
		pthread_mutex_lock(&philo->args->simulation_mutex);
		if (philo->args->simulation_finished)
		{
			pthread_mutex_unlock(&philo->args->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->args->simulation_mutex);
	}
}

static void	handle_odd_number_philos(t_philo *philo)
{
		while (1)
	{
		if (get_current_time() - philo->last_meal_time > philo->args->time_to_eat
			&& philo->args->time_to_eat < philo->args->time_to_sleep)
			usleep(500);
		else if (get_current_time() - philo->last_meal_time > philo->args->time_to_sleep)
			usleep(philo->args->time_to_eat - 2);
		print_state(philo, "is thinking");
		pthread_mutex_lock(&philo->meal_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		take_forks(philo, philo->id);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
		pthread_mutex_lock(&philo->args->simulation_mutex);
		if (philo->args->simulation_finished)
		{
			pthread_mutex_unlock(&philo->args->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->args->simulation_mutex);
	}
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->args->number_of_philos % 2 == 0)
		handle_even_number_philos(philo);
	else
		handle_odd_number_philos(philo);
	return (NULL);
}
