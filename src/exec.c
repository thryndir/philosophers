/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:47:35 by lgalloux          #+#    #+#             */
/*   Updated: 2024/06/09 22:50:09 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo, int philo_index)
{

}

void	philo_eat(t_philo *philo, int philo_index)
{
	take_fork(philo, philo_index);
	
}

void	philo_think(t_philo *philo)
{

}

void	philo_sleep(t_philo *philo)
{

}

void	philo_life(void *v_philo)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)v_philo;
	while (!is_dead())
	{
		philo_eat(philo, i);
		philo_think();
		philo_sleep();
		i++;
	}
}

void	create_philo(t_philo *philo)
{
	size_t		temp;
	size_t		i;

	i = 0;
	temp = philo->nbr_of_philo;
	while (temp)
	{
		pthread_create(philo->threads[i], NULL, &philo_life, philo);
		temp--;
	}
}
