/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:20:58 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/23 19:33:42 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_node *node)
{
	t_info	*info;

	info = node->info;
	pthread_mutex_lock(&node->right->u_u.fork->fork_lock);
	if (!atomic_load(&node->info->a_dead))
		writef(since_start(DISPLAY), node->index / 2, " has taken a fork\n");
	pthread_mutex_lock(&node->left->u_u.fork->fork_lock);
	if (!atomic_load(&node->info->a_dead))
		writef(since_start(DISPLAY), node->index / 2, " has taken a fork\n");
}

int	philo_eat(t_node *node)
{
	t_philo	*philo;
	t_info	*info;

	info = node->info;
	philo = node->u_u.philo;
	if (node->info->nbr_of_philo == 1 && !atomic_load(&node->info->a_dead))
	{
		writef(since_start(DISPLAY), node->index / 2, " has taken a fork\n");
		ft_usleep(info->time_to_die);
		return (1);
	}
	take_fork(node);
	pthread_mutex_lock(&philo->lock_death);
	atomic_store(&philo->last_eat, since_start(DISPLAY));
	if (!atomic_load(&info->a_dead))
		writef(since_start(DISPLAY), node->index / 2, " is eating\n");
	pthread_mutex_unlock(&philo->lock_death);
	ft_usleep(info->time_to_eat);
	atomic_fetch_add(&philo->nbr_of_eat, 1);
	pthread_mutex_unlock(&node->right->u_u.fork->fork_lock);
	pthread_mutex_unlock(&node->left->u_u.fork->fork_lock);
	return (0);
}

int	philo_think(t_node *node)
{
	t_info	*info;

	info = node->info;
	if (!atomic_load(&node->info->a_dead))
		writef(since_start(DISPLAY), node->index / 2, " is thinking\n");
	return (0);
}

int	philo_sleep(t_node *node)
{
	t_info	*info;

	info = node->info;
	if (!atomic_load(&node->info->a_dead))
		writef(since_start(DISPLAY), node->index / 2, " is sleeping\n");
	ft_usleep(info->time_to_sleep);
	return (0);
}

void	*philo_life(void *v_node)
{
	t_info	*info;
	t_philo	*philo;
	t_node	*node;

	node = (t_node *)v_node;
	info = node->info;
	philo = node->u_u.philo;
	if (node->index % 4 == 0)
		ft_usleep(1);
	while (!atomic_load(&info->a_dead))
	{
		if (atomic_load(&info->a_dead) || philo_eat(node))
			return (NULL);
		if (info->max_eat != -1 && is_full(node))
			return (NULL);
		if (atomic_load(&info->a_dead) || philo_sleep(node))
			return (NULL);
		if (atomic_load(&info->a_dead) || philo_think(node))
			return (NULL);
	}
	return (NULL);
}
