/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:37:29 by donheo            #+#    #+#             */
/*   Updated: 2025/06/06 20:53:36 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdatomic.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

// Shared configuration and simulation state
typedef struct s_args
{
	int				philo_num;
	long			start_time;
	long			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	int				died_philo;
	int				all_eaten;
	atomic_int		simulation_finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;

}	t_args;

// Philosopher-specific data
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args			*args;
	pthread_mutex_t	meal_mutex;
}	t_philo;

// ─────────────────────────────────────────────────────────────
// Thread routines
// ─────────────────────────────────────────────────────────────
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	put_forks(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	*philo_routine(void *ptr);
void	*handle_single_philo(void *ptr);

// ─────────────────────────────────────────────────────────────
// Utility functions
// ─────────────────────────────────────────────────────────────
long	get_current_time(void);
long	ft_atoi(const char *str);
int		is_str_valid_number(int argc, char **argv);
int		check_overflow_and_save_args(t_args *arg, \
int argc, char **argv, long tmp);
void	sleep_until(t_args *args, long target_time_ms);
int		finish_if_all_eaten(t_philo *philos, t_args *arg);

// ─────────────────────────────────────────────────────────────
// Output & Error handling
// ─────────────────────────────────────────────────────────────
void	print_state(t_philo *philo, const char *state);
void	print_died_philo(t_args *args);
void	print_error(char *error_message);

// ─────────────────────────────────────────────────────────────
// Cleanup & Resource management
// ─────────────────────────────────────────────────────────────
void	destroy_fork_mutexes(t_args *args, int fork_count);
void	cleanup_on_philo_failure(t_args *args);
void	cleanup_on_meal_failure(t_args *args, t_philo *philo, \
int meal_count);
void	cleanup_on_thread_failure(t_args *args, t_philo *philo, \
int thread_count);
void	cleanup_resources(t_args *args, t_philo *philo);

#endif
