/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:37:29 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 23:10:05 by donheo           ###   ########.fr       */
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

// Shared configuration and simulation state
typedef struct s_args
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	int				start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	simulation_mutex;
	int				simulation_finished;

}	t_args;

// Philosopher-specific data
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args			*args;
	pthread_mutex_t	meal_mutex;
}	t_philo;

// ─────────────────────────────────────────────────────────────
// Thread routines
// ─────────────────────────────────────────────────────────────
void	*philo_routine(void *ptr);

// ─────────────────────────────────────────────────────────────
// Utility functions
// ─────────────────────────────────────────────────────────────
int		get_current_time(void);
long	ft_atoi(const char *str);
void	is_str_valid_number(int argc, char **argv);
void	check_overflow_and_save_arg(t_args *arg, \
	int argc, char **argv, long tmp);
int		finish_if_all_eaten(t_philo *philos, t_args *arg);
int		handle_single_philo(t_philo *philo);

// ─────────────────────────────────────────────────────────────
// Output & Error handling
// ─────────────────────────────────────────────────────────────
void	print_state(t_philo *philo, const char *state);
void	exit_with_error(char *error_message);

// ─────────────────────────────────────────────────────────────
// Cleanup & Resource management
// ─────────────────────────────────────────────────────────────
void	cleanup_on_create_failure(t_args *arg, \
	t_philo *philo, int created_threads);
void	cleanup_resources(t_args *arg, t_philo *philo);

#endif
