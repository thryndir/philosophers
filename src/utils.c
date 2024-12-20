/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:56:30 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/20 15:09:47 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int			i;
	long		result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	if (str == NULL)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	nbr_size(char	*nbr)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	if (nbr[i] == '-')
		i++;
	while (nbr[i] == '0')
		i++;
	while (nbr[i])
	{
		i++;
		size++;
	}
	return (size);
}

size_t	since_start(int set_or_display)
{
	static size_t	start_time;

	if (set_or_display == SET)
		start_time = get_current_time();
	return (get_current_time() - start_time);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_usleep(size_t milliseconds)
{
	size_t start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
