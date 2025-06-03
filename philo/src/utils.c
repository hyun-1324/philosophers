/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:06:31 by donheo            #+#    #+#             */
/*   Updated: 2025/06/03 15:03:16 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_with_error(char *error_message)
{
	printf("%s\n", error_message);
	exit(EXIT_FAILURE);
}

int	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	ft_atoi(const char *str)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		if (sign == 1 && num > INT_MAX)
			return (0);
		else if (sign == -1 && (-1 * num) < INT_MIN)
			return (0);
		str++;
	}
	return (num * sign);
}

void	is_str_valid_number(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '\0')
			exit_with_error("invalid argument");
		if (argv[i][j] == '+')
		{
			j++;
			if (argv[i][j] == '\0')
				exit_with_error("invalid argument");
		}
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				exit_with_error("invalid argument");
			j++;
		}
		i++;
	}
}

void	check_overflow_and_save_arg(t_args *args, int argc, char **argv, long tmp)
{
	tmp = ft_atoi(argv[1]);
	if (tmp <= 0 || tmp > INT_MAX)
		exit_with_error("invalid number_of_philos");
	args->number_of_philos = (int)tmp;
	tmp = ft_atoi(argv[2]);
	if (tmp <= 0 || tmp > INT_MAX)
		exit_with_error("invalid time_to_die");
	args->time_to_die = (int)tmp;
	tmp = ft_atoi(argv[3]);
	if (tmp <= 0 || tmp > INT_MAX)
		exit_with_error("invalid time_to_eat");
	args->time_to_eat = (int)tmp;
	tmp = ft_atoi(argv[4]);
	if (tmp <= 0 || tmp > INT_MAX)
		exit_with_error("invalid time_to_sleep");
	args->time_to_sleep = (int)tmp;
	args->number_must_eat = -1;
	if (argc == 6)
	{
		tmp = ft_atoi(argv[5]);
		if (tmp <= 0 || tmp > INT_MAX)
			exit_with_error("invalid number_must_eat");
		args->number_must_eat = (int)tmp;
	}
}
