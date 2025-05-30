#include "philo.h"

int	init_arg(t_arg *arg, int argc, char **argv)
{
	int	i;

	arg->number_of_philos = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->number_must_eat = -1;
	if (argc == 6)
		arg->number_must_eat = ft_atoi(argv[5]);
	if (arg->number_of_philos <= 0 || arg->time_to_die <= 0 || arg->time_to_eat <= 0 || arg->time_to_sleep <= 0 || (arg == 6 && arg->number_must_eat <= 0))
		return (1);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->number_of_philos);
	if (!arg->forks)
		return (2);
	i = 0;
	while (i < arg->number_of_philos)
		pthread_mutex_init(&arg->forks[i], NULL);
	phtread_mutex_init(&arg->print_mutex, NULL);
	arg->simulation_finished = 0;
	arg->start_time = get_current_time();
	return (0);
}


int	main(int argc, char **argv)
{
	t_arg	arg;
	t_philo	*philo;
	int		errno;

	if (argc !=5 && argc != 6)
		return(3);
	memset(&arg, 0, sizeof(t_arg));
	errno = init_arg(&arg, argc, argv);
	if (errno)
		return(errno);
	errno = init_philo(&philo, &arg);
	if (error)
		return(errno);
	errno = ft_philo_start(&arg, philo);
	if (errno)
		return (errno);
	return (0);
}
