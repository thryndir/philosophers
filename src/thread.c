/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:47:35 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/23 19:27:40 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_die(t_node *node)
{
	int		current_time;
	int		last_eat_time;
	int		time_difference;
	bool	is_full;

	current_time = since_start(DISPLAY);
	last_eat_time = atomic_load(&node->u_u.philo->last_eat);
	is_full = atomic_load(&node->u_u.philo->is_full);
	time_difference = current_time - last_eat_time;
	return (time_difference >= node->info->time_to_die && !is_full);
}

void	*monitoring(void *v_node)
{
	t_node	*node;
	t_info	*info;

	node = (t_node *)v_node;
	info = node->info;
	while (1)
	{
		if (node->type == PHILO && should_die(node))
		{
			pthread_mutex_lock(&node->u_u.philo->lock_death);
			atomic_store(&info->a_dead, true);
			writef(since_start(DISPLAY), node->index / 2, " died\n");
			pthread_mutex_unlock(&node->u_u.philo->lock_death);
			return (NULL);
		}
		if (atomic_load(&info->nbr_full) >= info->nbr_of_philo)
			return (NULL);
		node = node->left;
		if (node->index == 0)
			ft_usleep(1);
	}
	return (NULL);
}

void	destroy_and_join(t_node *node)
{
	t_type		philo_or_fork;

	philo_or_fork = PHILO;
	while (1)
	{
		if (node->type == PHILO && philo_or_fork == PHILO)
		{
			pthread_join(node->u_u.philo->id, NULL);
			pthread_mutex_destroy(&node->u_u.philo->lock_death);
		}
		else if (node->type == FORK && philo_or_fork == FORK)
			pthread_mutex_destroy(&node->u_u.fork->fork_lock);
		node = node->left;
		if (node->index == 0 && philo_or_fork == PHILO)
			philo_or_fork = FORK;
		else if (node->index == 0 && philo_or_fork == FORK)
			break ;
	}
}

void	create_philo(t_node *node)
{
	pthread_t	monitor_id;
	t_type		philo_or_fork;

	philo_or_fork = PHILO;
	while (1)
	{
		if (node->type == PHILO)
			pthread_create(&node->u_u.philo->id, NULL, &philo_life, node);
		node = node->left;
		if (node->index == 0)
			break ;
	}
	pthread_create(&monitor_id, NULL, &monitoring, node);
	pthread_join(monitor_id, NULL);
	destroy_and_join(node);
}
