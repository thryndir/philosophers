/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:03:47 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/23 19:16:06 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_node(t_node *node)
{
	t_node	*temp;
	t_node	*last;

	last = ft_nodelast(node);
	while (node != last)
	{
		temp = node->left;
		if (node->type == PHILO)
			free(node->u_u.philo);
		else if (node->type == FORK)
			free(node->u_u.fork);
		free(node);
		node = temp;
	}
	if (node->type == PHILO)
		free(node->u_u.philo);
	else if (node->type == FORK)
		free(node->u_u.fork);
	free(node);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_node	*node;

	if (argc < 5 || argc > 6)
		return (write(1, "wrong number of argument\n", 25));
	if (verif_errors(argv, argc) != 0)
		return (1);
	since_start(SET);
	node = init(&info, argc, argv);
	create_philo(node);
	free_node(node);
}
