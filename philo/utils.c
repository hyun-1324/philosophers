/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:06:31 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 11:18:29 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

long long	current_timestamp(long long start_time)
{
	return (get_current_time() - start_time);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	print_state(t_philo *philo, const char *state)
{
	long long timestamp;

	pthread_mutex_lock(&philo->arg->print_mutex);
	if (!philo->arg->simulation_finished || ft_strncmp(state, "died", 4) == 0)
	{
		timestamp = get_current_time() - philo->arg->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, state);
	}
	pthread_mutex_unlock(&philo->arg->print_mutex);
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
