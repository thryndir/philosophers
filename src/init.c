/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:14:51 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/23 19:33:17 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_nodeadd_back(t_node **node, t_node *new, bool is_last)
{
	t_node	*tmp;

	if (*node == NULL)
		*node = new;
	else
	{
		tmp = ft_nodelast(*(node));
		tmp->left = new;
		new->right = tmp;
		if (is_last)
		{
			new->left = *node;
			(*node)->right = new;
		}
	}
}

t_philo	*ft_philonew(void)
{
	t_philo	*result;

	result = malloc(sizeof(t_philo));
	if (!result)
		return (NULL);
	result->last_eat = since_start(DISPLAY);
	result->nbr_of_eat = 0;
	result->is_full = false;
	pthread_mutex_init(&result->lock_death, NULL);
	result->id = 0;
	return (result);
}

t_fork	*ft_forknew(void)
{
	t_fork	*result;

	result = malloc(sizeof(t_fork));
	if (!result)
		return (NULL);
	pthread_mutex_init(&result->fork_lock, NULL);
	return (result);
}

t_node	*ft_nodenew(t_info *info, int index, int type)
{
	t_node	*result;

	result = malloc(sizeof(t_node));
	if (!result)
		return (NULL);
	result->index = index;
	result->type = type;
	result->info = info;
	if (type == PHILO)
		result->u_u.philo = ft_philonew();
	else if (type == FORK)
		result->u_u.fork = ft_forknew();
	result->left = NULL;
	result->right = NULL;
	return (result);
}

t_node	*init(t_info *info, int argc, char **argv)
{
	t_node	*node;
	t_node	*new;
	int		i;

	info->nbr_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->a_dead = false;
	info->max_eat = -1;
	info->nbr_full = 0;
	if (argc == 6)
		info->max_eat = ft_atoi(argv[5]);
	i = 1;
	node = ft_nodenew(info, 0, PHILO);
	while (i < info->nbr_of_philo * 2)
	{
		new = ft_nodenew(info, i, i % 2);
		if (i == info->nbr_of_philo * 2 - 1)
			ft_nodeadd_back(&node, new, true);
		else
			ft_nodeadd_back(&node, new, false);
		i++;
	}
	return (node);
}
