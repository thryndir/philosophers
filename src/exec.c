/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:47:35 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/21 21:25:38 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_r_fork(t_node *node)
{
	pthread_mutex_lock(&node->right->u_u.fork->fork_lock);
	if (!atomic_load(&node->info->a_dead))
		writef(since_start(DISPLAY), node->index / 2, " has taken a fork\n");
}

void	take_fork(t_node *node)
{
	t_info	*info;

	info = node->info;
	if (node->index % 4 == 0)
		take_r_fork(node);
	pthread_mutex_lock(&node->left->u_u.fork->fork_lock);
	if (!atomic_load(&node->info->a_dead))
		writef(since_start(DISPLAY), node->index / 2, " has taken a fork\n");
	if (node->index % 4 != 0)
		take_r_fork(node);
}

int	philo_eat(t_node *node)
{
	t_philo *philo;
	t_info 	*info;

	info = node->info;
	philo = node->u_u.philo;
	if (node->info->nbr_of_philo == 1 && !atomic_load(&node->info->a_dead))
	{
		writef(since_start(DISPLAY), node->index / 2, " has taken a fork\n");
		while (!atomic_load(&node->info->a_dead))
			ft_usleep(1);
		return (1);
	}
	take_fork(node);
	atomic_store(&philo->last_eat, since_start(DISPLAY));
	if (!atomic_load(&info->a_dead))
		writef(since_start(DISPLAY), node->index / 2, " is eating\n");
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

void	writef(size_t timestamp, int x, char *message)
{
	char *tsp;
	char *index;
	char *to_write;
	char *temp;

	index = ft_itoa(x);
	tsp = ft_itoa(timestamp);
	to_write = ft_strjoin(tsp, " ");
	free(tsp);
	temp = to_write;
	to_write = ft_strjoin(to_write, index);
	free(index);
	free(temp);
	to_write = ft_strjoin(to_write, message);
	write(1, to_write, ft_strlen(to_write));
	free(to_write);
}

bool should_die(t_node *node)
{
	size_t	current_time;
	size_t	last_eat_time;
	size_t	time_difference;
	bool	is_full;

	current_time = since_start(DISPLAY);
	last_eat_time = atomic_load(&node->u_u.philo->last_eat);
	is_full = atomic_load(&node->u_u.philo->is_full);
	time_difference = current_time - last_eat_time;
	return (time_difference >= node->info->time_to_die && !is_full);
}

void	*monitoring(void *v_node)
{
	t_node 	*node;
	t_info	*info;

	node = (t_node *)v_node;
	info = node->info;
	while (1)
	{
		if (node->type == PHILO && should_die(node))
		{
			atomic_store(&info->a_dead, true);
			writef(since_start(DISPLAY), node->index / 2, " died\n");
			return (NULL);
		}
		if (atomic_load(&info->nbr_full) >= info->nbr_of_philo)
			return NULL;
		node = node->left;
		if (node->index == 0)
			ft_usleep(1);
	}
	return (NULL);
}

void	*philo_life(void *v_node)
{
	t_info	*info;
	t_philo	*philo;
	t_node	*node;

	node = (t_node *)v_node;
	info = node->info;
	philo = node->u_u.philo;
	while (!atomic_load(&info->a_dead))
	{
		if (atomic_load(&info->a_dead) || philo_eat(node))
			return (NULL);
		if (info->max_eat != -1 && atomic_load(&philo->nbr_of_eat)
			>= info->max_eat)
		{
			pthread_mutex_lock(&info->check_death);
			atomic_store(&philo->is_full, true);
			atomic_fetch_add(&info->nbr_full, 1);
			pthread_mutex_unlock(&info->check_death);
			return (NULL);
		}
		if (atomic_load(&info->a_dead) || philo_sleep(node))
			return (NULL);
		if (atomic_load(&info->a_dead) || philo_think(node))
			return (NULL);
	}
	return (NULL);
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
			break;
	}
	pthread_create(&monitor_id, NULL, &monitoring, node);
	pthread_join(monitor_id, NULL);
	while (1)
	{
		if (node->type == PHILO && philo_or_fork == PHILO)
			pthread_join(node->u_u.philo->id, NULL);
		else if (node->type == FORK && philo_or_fork == FORK)
			pthread_mutex_destroy(&node->u_u.fork->fork_lock);
		node = node->left;
		if (node->index == 0 && philo_or_fork == PHILO)
			philo_or_fork = FORK;
		else if (node->index == 0 && philo_or_fork == FORK)
			break;
	}
	pthread_mutex_destroy(&node->info->check_death);
}
