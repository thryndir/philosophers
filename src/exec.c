/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:47:35 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/18 18:27:22 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_r_fork(t_node *node)
{
	pthread_mutex_lock(&node->right->u_u.fork->fork_lock);
	node->u_u.philo->nbr_of_fork++;
	printf("philo %d has taken the his right fork %d\n", node->index, node->right->index);
}

void	take_fork(t_info *info)
{
	t_node	*node;

	node = info->node;
	if (node->index % 4 == 0)
		take_r_fork(node);
	pthread_mutex_lock(&node->left->u_u.fork->fork_lock);
	node->u_u.philo->nbr_of_fork++;
	printf("philo %d has taken his left fork %d\n", node->index, node->left->index);
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
	if (get_current_time() - philo->last_eat >= info->time_to_die)
	{
		philo->is_dead = true;
		writef(get_current_time(), node->index, " died\n");
		return (1);
	}
	printf("le philo %d a %d fork\n", node->index, node->u_u.philo->nbr_of_fork);
	writef(get_current_time(), node->index, " is eating\n");
	ft_usleep(info->time_to_eat);
	philo->nbr_of_eat++;
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&node->right->u_u.fork->fork_lock);
	printf("philo %d let go of his right fork %d\n", info->node->index, node->right->index);
	pthread_mutex_unlock(&node->left->u_u.fork->fork_lock);
	printf("philo %d let go of his left fork %d\n", info->node->index, node->left->index);
	philo->nbr_of_fork = 0;
	return (0);
}

int	philo_think(t_info *info)
{
	t_philo	*philo;
	t_node	*node;

	node = info->node;
	philo = node->u_u.philo;
	if (get_current_time() - philo->last_eat >= info->time_to_die)
	{
		philo->is_dead = true;
		writef(get_current_time(), node->index, " died\n");
		return (1);
	}
	writef(get_current_time(), node->index, " is thinking\n");
	return (0);
}

int	philo_sleep(t_info *info)
{
	t_philo *philo;
	t_node	*node;

	node = info->node;
	philo = node->u_u.philo;
	if (get_current_time() - philo->last_eat 
		>= info->time_to_die || get_current_time() - philo->last_eat 
		+ info->time_to_sleep >= info->time_to_die)
	{
		philo->is_dead = true;
		writef(get_current_time(), node->index, " died\n");
		return (1);
	}
	writef(get_current_time(), node->index, " is sleeping\n");
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

void	*philo_life(void *v_info)
{
	t_info	*info;
	t_philo	*philo;

	info = (t_info *)v_info;
	// write(1, "test\n", 5);
	printf("l'index du philo est %d\n", info->node->index);
	return (NULL);
	philo = info->node->u_u.philo;
	while (!info->a_dead)
	{
		if (info->max_eat != -1 && philo->nbr_of_eat >= info->max_eat)
		{
			printf("c'est bon %d a bien mange", info->node->index);
			return (NULL);
		}
		if (info->a_dead || philo_eat(info))
		{
			if (info->a_dead)
				writef(get_current_time(), info->node->index, " ah il y a un mort\n");
			else
				writef(get_current_time(), info->node->index, " il est mort en mangeant\n");
			break;
		}
		if (info->a_dead || philo_sleep(info))
		{
			if (info->a_dead)
				writef(get_current_time(), info->node->index, " ah il y a un mort\n");
			else
				writef(get_current_time(), info->node->index, " il est mort en dormant\n");
			break;
		}
		if (info->a_dead || philo_think(info))
		{
			if (info->a_dead)
				writef(get_current_time(), info->node->index, " ah il y a un mort\n");
			else
				writef(get_current_time(), info->node->index, " il est mort en pensant\n");
			break;
		}
	}
	info->a_dead = true;
	printf("ah %d c'est bien termine\n", info->node->index);
	return (NULL);
}

void	create_philo(t_info info)
{
	while (1)
	{
		if (info.node->type == PHILO)
		{
			printf("l'index du philo dans create_philo est %d\n", info.node->index);
			pthread_create(&info.node->u_u.philo->id, NULL, &philo_life, &info);
		}
		else if (info.node->type == FORK)
		{
			printf("l'index de la fork dans create_philo est %d\n", info.node->index);
			pthread_mutex_init(&info.node->u_u.fork->fork_lock, NULL);
		}
		usleep(100);
		info.node = info.node->left;
		if (info.node->index == 0)
			break;
	}
	while (1)
	{
		if (info.node->type == PHILO)
			pthread_join(info.node->u_u.philo->id, NULL);
		else if (info.node->type == FORK)
			pthread_mutex_destroy(&info.node->u_u.fork->fork_lock);
		info.node = info.node->left;
		if (info.node->index == 0)
			break;
	}
}
