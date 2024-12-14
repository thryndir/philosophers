/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:03:47 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/14 12:47:12 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_info info;
	t_node *node;

	if (argc < 5 || argc > 6)
		return (1);
	info.node = init(&info, argc, argv);
	node = info.node;
	while (node != ft_nodelast(node))
	{
		printf("l'index du node est %d", node->index);
		node = node->next;
	}
	create_philo(node, info);
}
