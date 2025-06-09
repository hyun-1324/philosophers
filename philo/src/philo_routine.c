/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:18:45 by donheo            #+#    #+#             */
/*   Updated: 2025/06/09 18:54:35 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_even_number_philos(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->args->simulation_finished)
	{
		print_state(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
	}
}

static void	handle_odd_number_philos(t_philo *philo)
{
	while (!philo->args->simulation_finished)
	{
		print_state(philo, "is thinking");
		if (get_current_time() - philo->last_meal_time > 50)
			sleep_until(philo->args, \
get_current_time() - 2 + philo->args->time_to_eat);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
	}
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->args->philo_num % 2 == 0)
		handle_even_number_philos(philo);
	else
		handle_odd_number_philos(philo);
	return (NULL);
}
