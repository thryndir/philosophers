/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:14:51 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/21 21:28:45 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_node	*ft_nodelast(t_node *node)
{
	if (node == NULL)
			return (NULL);
	while (node->left && node->left->index > node->index)
		node = node->left;
	return (node);
}

void	print_node(t_node *node)
{
	t_node *current;

	current = node;
	while (1)
	{
		printf("le node %d, a pour type %d\n", current->index, current->type);
		if (current->right)
			printf("le node %d a pour right %d, qui est du type %d\n", current->index, current->right->index, current->right->type);
		else
			printf("le node %d n'a pas de right\n", current->index);
		if (current->left)
		printf("le node %d a pour left %d, qui est du type %d\n", current->index, current->left->index, current->left->type);
		else
			printf("le node %d n'a pas de left\n", current->index);
		current = current->left;
		if (current->index == 0)
			break;
	}
}

void	ft_nodeadd_back(t_node **node, t_node *new, bool is_last)
{
	t_node  *tmp;

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
	result->id = 0;
	return (result);
}

t_fork *ft_forknew(void)
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
	t_node  *result;

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

t_node *init_node(t_info *info)
{
	t_node *node;
	t_node *new;
	int		i;

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

void	init_info(t_info *info, int argc, char **argv)
{
	info->nbr_of_philo = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	info->a_dead = false;
	info->max_eat = -1;
	info->nbr_full = 0;
	if (argc == 6)
	info->max_eat = ft_atol(argv[5]);
	pthread_mutex_init(&info->check_death, NULL);
}

t_node	*init(t_info *info, int argc, char **argv)
{
	t_node *node;

	init_info(info, argc, argv);
	node = init_node(info);
	return (node);
}
