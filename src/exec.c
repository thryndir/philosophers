/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:47:35 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/13 17:10:11 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{

}

void	philo_eat(t_philo *philo)
{
	take_fork(philo, philo_index);
	
}

void	philo_think(t_philo *philo)
{

}

void	philo_sleep(t_philo *philo)
{

}

void	philo_life(void *v_node)
{
	t_philo	*philo;

	philo = (t_philo *)v_node->u_u.philo;
	while (!philo->is_dead)
	{
		philo_eat(philo, i);
		philo_think();
		philo_sleep();
		i++;
	}
}

void	create_philo(t_node *node, t_info info)
{
	size_t		i;

	i = 0;
	while (node != ft_nodelast(node))
	{
		if (node->type == PHILO)
			pthread_create(node->u_u.philo->tid, NULL, &philo_life, node);
		node = node->next;
	}
}
