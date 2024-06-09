/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:14:51 by thryndir          #+#    #+#             */
/*   Updated: 2024/06/09 22:32:30 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_philo *philo, char **argv, int argc)
{
	int	i;

	i = 0;
	philo->nbr_of_philo = argv[1];
	philo->time_to_die = argv[2];
	philo->time_to_eat = argv[3];
	philo->time_to_sleep = argv[4];

	while (i <= philo->nbr_of_philo)
	{
		philo->forks[i] = 0;
		i++;
	}
	if (argc == 5)
		philo->nbr_of_eat = argv[5];
	else
		philo->nbr_of_eat = 0;
}
