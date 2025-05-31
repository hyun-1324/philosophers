/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:37:29 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 11:03:25 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_arg
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				simulation_finished;

}	t_arg;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_arg			*arg;
	pthread_mutex_t	meal_mutex;
} t_philo;

void		*philo_routine(void *ptr);
void		*monitor_routine(void *arg);

long		ft_atoi(const char *str);
long long	get_current_time(void);
long long	current_timestamp(long long start_time);
void		print_state(t_philo *philo, const char *state);

void	cleanup_on_create_failure(t_arg *arg, t_philo *philo, int created_threads);
void	cleanup_resources(t_arg *arg, t_philo *philo);

#endif
