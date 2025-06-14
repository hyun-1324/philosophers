/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:09:26 by donheo            #+#    #+#             */
/*   Updated: 2025/06/06 20:43:27 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *error_message)
{
	printf("%s\n", error_message);
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

void	print_died_philo(t_args *args)
{
	long	timestamp;

	usleep(1000);
	timestamp = get_current_time() - args->start_time;
	if (!args->all_eaten)
		printf("%ld %d %s\n", timestamp, args->died_philo, "died");
}

void	print_state(t_philo *philo, const char *state)
{
	char	buffer[50];
	int		pos;
	int		len;
	int		timestamp;

	pos = 0;
	if (!philo->args->simulation_finished)
	{
		pthread_mutex_lock(&philo->args->print_mutex);
		timestamp = get_current_time() - philo->args->start_time;
		pos += ft_itoa(timestamp, buffer + pos);
		buffer[pos++] = ' ';
		pos += ft_itoa(philo->id, buffer + pos);
		buffer[pos++] = ' ';
		len = 0;
		while (state[len])
			buffer[pos++] = state[len++];
		buffer[pos++] = '\n';
		write(STDOUT_FILENO, buffer, pos);
		pthread_mutex_unlock(&philo->args->print_mutex);
	}
}
