/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:06:31 by donheo            #+#    #+#             */
/*   Updated: 2025/06/06 20:54:25 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
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

int	is_str_valid_number(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '\0')
			return (print_error("invalid argument"), 0);
		if (argv[i][j] == '+')
		{
			j++;
			if (argv[i][j] == '\0')
				return (print_error("invalid argument"), 0);
		}
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (print_error("invalid argument"), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_overflow_and_save_args(t_args *args, \
int argc, char **argv, long tmp)
{
	tmp = ft_atoi(argv[1]);
	if (tmp <= 0 || tmp > INT_MAX)
		return (print_error("invalid number_of_philos"), 0);
	args->philo_num = (int)tmp;
	tmp = ft_atoi(argv[2]);
	if (tmp <= 0 || tmp > INT_MAX)
		return (print_error("invalid time_to_die"), 0);
	args->time_to_die = (int)tmp;
	tmp = ft_atoi(argv[3]);
	if (tmp <= 0 || tmp > INT_MAX)
		return (print_error("invalid time_to_eat"), 0);
	args->time_to_eat = (int)tmp;
	tmp = ft_atoi(argv[4]);
	if (tmp <= 0 || tmp > INT_MAX)
		return (print_error("invalid time_to_sleep"), 0);
	args->time_to_sleep = (int)tmp;
	args->number_must_eat = -1;
	if (argc == 6)
	{
		tmp = ft_atoi(argv[5]);
		if (tmp <= 0 || tmp > INT_MAX)
			return (print_error("invalid number_must_eat"), 0);
		args->number_must_eat = (int)tmp;
	}
	return (1);
}
