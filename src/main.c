/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:03:47 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/13 15:17:02 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_info info;
	t_node *node;

	if (argc < 5 || argc > 6)
		return (1);
	node = init(&info, argc, argv);
	while (node != ft_nodelast(node))
	{
		printf("l'index du node est %d", node->index);
		node = node->next;
	}
}
