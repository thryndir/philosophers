/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:47:35 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/14 19:19:45 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_r_fork(t_node *node)
{
	pthread_mutex_lock(node->next->u_u.fork->fork_lock);
	node->u_u.philo->nbr_of_fork++;
	writef(get_current_time(), node->index / 2, " has taken a fork\n");
}

int	take_fork(t_info *info)
{
	t_philo *philo;
	t_node	*node;

	node = info->node;
	philo = info->node->u_u.philo;
	if (node->index % 4 == 0)
		take_r_fork(node);
	pthread_mutex_lock(node->prev->u_u.fork->fork_lock);
	node->u_u.philo->nbr_of_fork++;
	writef(get_current_time(), node->index / 2, " has taken a fork\n");
	if (node->index % 4 != 0)
		take_r_fork(node);
}

int	philo_eat(t_info *info)
{
	t_philo *philo;
	t_node	*node;

	node = info->node;
	philo = node->u_u.philo;
	take_fork(info);
	if (philo->last_eat - get_current_time() >= info->time_to_die)
	{
		philo->is_dead = true;
		writef(get_current_time(), node->index / 2, " died\n");
		return (1);
	}
	writef(get_current_time(), node->index / 2, " is eating\n");
	ft_usleep(info->time_to_eat);
	philo->nbr_of_eat++;
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(node->prev->u_u.fork->fork_lock);
	pthread_mutex_unlock(node->next->u_u.fork->fork_lock);
	return (0);
}

int	philo_think(t_info *info)
{
	t_philo	*philo;
	t_node	*node;

	node = info->node;
	philo = node->u_u.philo;
	if (philo->last_eat - get_current_time() >= info->time_to_die)
	{
		philo->is_dead = true;
		writef(get_current_time(), node->index / 2, " died\n");
		return (1);
	}
	writef(get_current_time(), node->index / 2, " is thinking\n");
	return (0);
}

int	philo_sleep(t_info *info)
{
	t_philo *philo;
	t_node	*node;

	node = info->node;
	philo = node->u_u.philo;
	if (philo->last_eat - get_current_time() 
		>= info->time_to_die || philo->last_eat - get_current_time() 
		+ info->time_to_sleep >= info->time_to_die)
	{
		philo->is_dead = true;
		writef(get_current_time(), node->index / 2, " died\n");
		return (1);
	}
	writef(get_current_time(), node->index / 2, " is sleeping\n");
	ft_usleep(info->time_to_sleep);
	return (0);
}

void	writef(long timestamp, int x, char *message)
{
	char *tsp;
	char *index;
	char *to_write;
	char *temp;

	index = ft_itoa(x);
	tsp = ft_itoa((int)timestamp);
	to_write = ft_strjoin(tsp, " ");
	free(tsp);
	temp = to_write;
	to_write = ft_strjoin(to_write, index);
	free(index);
	free(temp);
	to_write = ft_strjoin(to_write, message);
	write(1, &to_write, ft_strlen(to_write));
	free(to_write);
}

void	philo_life(void *v_info)
{
	t_info	*info;
	t_philo	*philo;

	info = (t_info *)v_info;
	philo = info->node->u_u.philo;
	if (info->max_eat == -1)
	while (!info->a_dead)
	{
		if (info->max_eat != -1 && philo->nbr_of_eat >= info->max_eat)
			return (0);
		else if (info->a_dead || philo_eat(info))
			break;
		else if (info->a_dead || philo_sleep(info))
			break;
		else if (info->a_dead || philo_think(info))
			break;
	}
	info->a_dead = true;
}

void	create_philo(t_info info)
{
	size_t		i;

	i = 0;
	while (info.node != ft_nodelast(info.node))
	{
		if (info.node->type == PHILO)
			pthread_create(info.node->u_u.philo->id, NULL, &philo_life, &info);
		else if (info.node->type == FORK)
			pthread_mutex_init(info.node->u_u.fork->fork_lock, NULL);
		info.node = info.node->next;
	}
	info.node = info.node->next;
	while (info.node != ft_nodelast(info.node))
	{
		if (info.node->type == PHILO)
			pthread_join(info.node->u_u.philo->id, NULL);
		else if (info.node->type == FORK)
			pthread_mutex_destroy(info.node->u_u.fork->fork_lock);
		info.node = info.node->next;
	}
}
