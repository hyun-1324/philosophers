/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:09:26 by donheo            #+#    #+#             */
/*   Updated: 2025/05/31 20:39:53 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	ft_itoa(int n, char *buf)
{
	int		len;
	char	tmp[12];
	int		i;

	len = 0;
	if (n == 0)
	{
		buf[0] = '0';
		return (1);
	}
	while (n > 0)
	{
		tmp[len++] = '0' + (n % 10);
		n /= 10;
	}
	i = 0;
	while (i < len)
	{
		buf[i] = tmp[len - i - 1];
		i++;
	}
	return (len);
}

void	print_state(t_philo *philo, const char *state)
{
	char	buffer[50];
	int		pos;
	int		len;
	int		timestamp;

	pos = 0;
	pthread_mutex_lock(&philo->arg->simulation_mutex);
	if (!philo->arg->simulation_finished || ft_strncmp(state, "died", 4) == 0)
	{
		pthread_mutex_unlock(&philo->arg->simulation_mutex);
		pthread_mutex_lock(&philo->arg->print_mutex);
		timestamp = get_current_time() - philo->arg->start_time;
		pos += ft_itoa(timestamp, buffer + pos);
		buffer[pos++] = ' ';
		pos += ft_itoa(philo->id, buffer + pos);
		buffer[pos++] = ' ';
		len = 0;
		while (state[len])
			buffer[pos++] = state[len++];
		buffer[pos++] = '\n';
		write(STDOUT_FILENO, buffer, pos);
		pthread_mutex_unlock(&philo->arg->print_mutex);
	}
	else
		pthread_mutex_unlock(&philo->arg->simulation_mutex);
}
