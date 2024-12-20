/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:47:35 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/20 19:13:28 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_r_fork(t_node *node)
{
	pthread_mutex_lock(&node->right->u_u.fork->fork_lock);
	if (!node->info->a_dead)
		writef(since_start(DISPLAY), node->index / 2, " has taken a fork\n");
}

void	take_fork(t_node *node)
{
	if (node->index % 4 == 0)
		take_r_fork(node);
	pthread_mutex_lock(&node->left->u_u.fork->fork_lock);
	if (!node->info->a_dead)
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
	if (node->info->nbr_of_philo == 1 && !node->info->a_dead)
	{
		writef(since_start(DISPLAY), node->index / 2, " has taken a fork\n");
		while (1)
		{
			if (node->info->a_dead)
				return (1);
		}
	}
	take_fork(node);
	if (!node->info->a_dead)
		writef(since_start(DISPLAY), node->index / 2, " is eating\n");
	ft_usleep(info->time_to_eat);
	philo->nbr_of_eat++;
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&node->right->u_u.fork->fork_lock);
	pthread_mutex_unlock(&node->left->u_u.fork->fork_lock);
	return (0);
}

int	philo_think(t_node *node)
{
	if (node->info->nbr_of_philo == 1)
		return (0);
	if (!node->info->a_dead)
		writef(since_start(DISPLAY), node->index / 2, " is thinking\n");
	return (0);
}

int	philo_sleep(t_node *node)
{
	t_info	*info;

	info = node->info;
	if (node->info->nbr_of_philo == 1)
		return (0);
	if (!node->info->a_dead)
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

void	*monitoring(void *v_node)
{
	t_node 	*node;
	t_info	*info;
	int current_nbr_full;

	node = (t_node *)v_node;
	info = node->info;
	while (1)
	{
		pthread_mutex_lock(&info->check_full);
		current_nbr_full = info->nbr_full;
		pthread_mutex_unlock(&info->check_full);

		printf("nbr_full protégé: %d, max_eat: %d\n", current_nbr_full, info->max_eat);

		if (node->type == PHILO && get_current_time()
			- node->u_u.philo->last_eat >= info->time_to_die 
			&& !node->u_u.philo->is_full)
		{
			info->a_dead = true;
			writef(since_start(DISPLAY), node->index / 2, " died\n");
			return (NULL);
		}
		if (current_nbr_full >= info->max_eat)
			return NULL;
		node = node->left;
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
	while (!info->a_dead)
	{
		if (info->max_eat != -1 && philo->nbr_of_eat >= info->max_eat)
		{
			pthread_mutex_lock(&info->check_full);
			if (!philo->is_full)
			{
				philo->is_full = true;
				info->nbr_full++;
				printf("Philosophe %d est plein, nbr_full maintenant: %d\n", 
					node->index / 2, info->nbr_full);
			}
			pthread_mutex_unlock(&info->check_full);
			return (NULL);
		}
		if (info->a_dead || philo_eat(node))
			break;
		if (info->a_dead || philo_sleep(node))
			break;
		if (info->a_dead || philo_think(node))
			break;
	}
	return (NULL);
}

void	create_philo(t_node *node)
{
	pthread_t	id;

	while (1)
	{
		if (node->type == PHILO)
			pthread_create(&node->u_u.philo->id, NULL, &philo_life, node);
		node = node->left;
		if (node->index == 0)
			break;
	}
	pthread_create(&id, NULL, &monitoring, node);
	pthread_join(id, NULL);
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
	pthread_mutex_destroy(&node->info->check_full);
}
