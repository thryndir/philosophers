/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:47:35 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/20 14:34:03 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_r_fork(t_node *node)
{
	pthread_mutex_lock(&node->right->u_u.fork->fork_lock);
	node->u_u.philo->nbr_of_fork++;
	writef(time_since_start(DISPLAY), node->index, " has taken a fork\n");
}

void	take_fork(t_node *node)
{
	if (node->index % 4 == 0)
		take_r_fork(node);
	pthread_mutex_lock(&node->left->u_u.fork->fork_lock);
	node->u_u.philo->nbr_of_fork++;
	writef(time_since_start(DISPLAY), node->index, " has taken a fork\n");
	if (node->index % 4 != 0)
		take_r_fork(node);
}

int	philo_eat(t_node *node)
{
	t_philo *philo;
	t_info 	*info;

	info = node->info;
	philo = node->u_u.philo;
	if (node->info->nbr_of_philo == 1)
		return (0);
	take_fork(node);
	if (get_current_time() - philo->last_eat >= info->time_to_die)
	{
		pthread_mutex_unlock(&node->right->u_u.fork->fork_lock);
		pthread_mutex_unlock(&node->left->u_u.fork->fork_lock);
		philo->is_dead = true;
		writef(time_since_start(DISPLAY), node->index, " died\n");
		return (1);
	}
	printf("le philo %d a %d fork\n", node->index, node->u_u.philo->nbr_of_fork);
	writef(time_since_start(DISPLAY), node->index, " is eating\n");
	ft_usleep(info->time_to_eat);
	philo->nbr_of_eat++;
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&node->right->u_u.fork->fork_lock);
	pthread_mutex_unlock(&node->left->u_u.fork->fork_lock);
	philo->nbr_of_fork = 0;
	return (0);
}

int	philo_think(t_node *node)
{
	t_philo	*philo;
	t_info	*info;

	info = node->info;
	philo = node->u_u.philo;
	if (get_current_time() - philo->last_eat >= info->time_to_die)
	{
		philo->is_dead = true;
		writef(time_since_start(DISPLAY), node->index, " died\n");
		return (1);
	}
	writef(time_since_start(DISPLAY), node->index, " is thinking\n");
	return (0);
}

int	philo_sleep(t_node *node)
{
	t_philo *philo;
	t_info	*info;

	info = node->info;
	philo = node->u_u.philo;
	if (get_current_time() - philo->last_eat 
		>= info->time_to_die || get_current_time() - philo->last_eat 
		+ info->time_to_sleep >= info->time_to_die)
	{
		philo->is_dead = true;
		writef(time_since_start(DISPLAY), node->index, " died\n");
		return (1);
	}
	writef(time_since_start(DISPLAY), node->index, " is sleeping\n");
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

void	*philo_life(void *v_node)
{
	t_info	*info;
	t_philo	*philo;
	t_node	*node;

	node = (t_node *)v_node;
	info = node->info;
	// pthread_mutex_unlock(&info->sync_create);
	philo = node->u_u.philo;
	
	while (!info->a_dead)
	{
		if (info->max_eat != -1 && philo->nbr_of_eat >= info->max_eat)
		{
			printf("c'est bon %d a bien mange\n", node->index);
			return (NULL);
		}
		if (info->a_dead || philo_eat(node))
		{
			if (info->a_dead)
				writef(time_since_start(DISPLAY), node->index, " ah il y a un mort\n");
			else
				writef(time_since_start(DISPLAY), node->index, " il est mort en mangeant\n");
			break;
		}
		if (info->a_dead || philo_sleep(node))
		{
			if (info->a_dead)
				writef(time_since_start(DISPLAY), node->index, " ah il y a un mort\n");
			else
				writef(time_since_start(DISPLAY), node->index, " il est mort en dormant\n");
			break;
		}
		if (info->a_dead || philo_think(node))
		{
			if (info->a_dead)
				writef(time_since_start(DISPLAY), node->index, " ah il y a un mort\n");
			else
				writef(time_since_start(DISPLAY), node->index, " il est mort en pensant\n");
			break;
		}
	}
	info->a_dead = true;
	return (NULL);
}

void	create_philo(t_node *node)
{
	while (1)
	{
		if (node->type == PHILO)
			pthread_create(&node->u_u.philo->id, NULL, &philo_life, node);
		node = node->left;
		if (node->index == 0)
			break;
	}
	while (1)
	{
		if (node->type == PHILO)
			pthread_join(node->u_u.philo->id, NULL);
		else if (node->type == FORK)
			pthread_mutex_destroy(&node->u_u.fork->fork_lock);
		node = node->left;
		if (node->index == 0)
			break;
	}
	pthread_mutex_destroy(&node->info->sync_create);
}
