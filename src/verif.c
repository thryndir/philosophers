/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:01:24 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/13 15:20:39 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	only_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (((argv[i][j] < '0' || (argv[i][j] > '9')) && argv[i][j] != '-')
			|| (argv[i][j] == '-' && (argv[i][j + 1] < '0'
			|| argv[i][j + 1] > '9')))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	sup_to_maxint(char	**argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if ((nbr_size(argv[i]) > 10) || (ft_atol(argv[i]) > INT_MAX
				&& argv[i][0] != '-') || (ft_atol(argv[i]) < INT_MIN))
			return (1);
		i++;
	}
	return (0);
}

void	verif_errors(char **argv)
{
	if (!only_digit(argv))
		write(1, "error in parsing", 17);
	if (sup_to_maxint(argv))
		write(1, "error in parsing", 17);
	if (ft_atol(argv[1]) > 200)
		write(1, "error in parsing", 17);
}