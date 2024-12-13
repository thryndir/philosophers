/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:14:51 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/13 15:18:03 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_node	*ft_nodelast(t_node *node)
{
	int	prev_index;

	prev_index = -1;
	if (node == NULL)
			return (NULL);
	while (node->index > prev_index)
	{
		prev_index = node->index;
		node = node->next;
	}
	return (node);
}

void	ft_nodeadd_back(t_node **node, t_node *new, bool is_last)
{
	t_node  *tmp;

	if (*node == NULL)
			*node = new;
	else
	{
		tmp = ft_nodelast(*(node));
		tmp->next = new;
		new->prev = tmp;
		if (is_last)
			new->next = *node;
	}
}

t_philo	*ft_philonew()
{
	t_philo	*result;

	result = malloc(sizeof(t_philo));
	if (!result)
		return (NULL);
	result->last_eat = -1;
	result->nbr_of_eat = 0;
	result->nbr_of_fork = 0;
	return (result);
}

t_fork *ft_forknew()
{
	t_fork	*result;

	result = malloc(sizeof(t_fork));
	if (!result)
		return (NULL);
	result->is_used = false;
	return (result);
}

t_node	*ft_nodenew(int index, int type)
{
	t_node  *result;

	result = malloc(sizeof(t_node));
	if (!result)
			return (NULL);
	result->index = index;
	result->type = type;
	if (type == PHILO)
		result->u_u.philo = ft_philonew();
	else
		result->u_u.fork = ft_forknew();
	result->next = NULL;
	result->prev = NULL;
	return (result);
}

t_node	*init(t_info *info, int argc, char **argv)
{
	long	i;
	t_node *node;
	t_node	*new;

	i = 0;
	info->nbr_of_philo = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	if (argc == 5)
		info->max_eat = ft_atol(argv[5]);
	else
		info->max_eat = -1;
	node = ft_nodenew(i, i % 2);
	i++;
	while (i <= info->nbr_of_philo)
	{
		new = ft_nodenew(i, i % 2);
		if (i == info->nbr_of_philo)
			ft_nodeadd_back(&node, new, true);
		else
			ft_nodeadd_back(&node, new, false);
		i++;
	}
	return (node);
}
