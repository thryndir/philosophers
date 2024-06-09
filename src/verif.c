/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:01:24 by thryndir          #+#    #+#             */
/*   Updated: 2024/06/09 22:25:41 by lgalloux         ###   ########.fr       */
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
		if ((nbr_size(argv[i]) > 10) || (ft_atoll(argv[i]) > INT_MAX
				&& argv[i][0] != '-') || (ft_atoll(argv[i]) < INT_MIN))
			return (1);
		i++;
	}
	return (0);
}

void	verif_errors(char **argv)
{
	if (!only_digit(argv))
		ft_error(argv, 1);
	if (sup_to_maxint(argv))
		ft_error(argv, 2);
	if (ft_atoll(argv[1]) > 200)
		ft_error(argv, 3)
}