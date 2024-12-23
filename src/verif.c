/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:01:24 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/23 17:52:44 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	only_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		while (arg[i])
		{
			if (arg[i] < '0' || arg[i] > '9')
				return (false);
			i++;
		}
	}
	return (true);
}

int	verif_errors(char **argv, int argc)
{
	if (ft_atoi(argv[1]) < 0 || !only_digit(argv[1]))
		return (write(1, "wrong philo number\n", 20));
	if (ft_atoi(argv[2]) < 0 || !only_digit(argv[2]))
		return (write(1, "wrong time to die\n", 19));
	if (ft_atoi(argv[3]) < 0 || !only_digit(argv[3]))
		return (write(1, "wrong time to eat\n", 19));
	if (ft_atoi(argv[4]) < 0 || !only_digit(argv[4]))
		return (write(1, "wrong time to sleep\n", 19));
	if (argc == 6 && (ft_atoi(argv[5]) < 0 || !only_digit(argv[5])))
		return (write(1, "wrong max_eat number\n", 22));
	return (0);
}
