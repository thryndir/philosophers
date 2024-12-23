/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:26:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/23 19:33:52 by lgalloux         ###   ########.fr       */
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

void	writef(int timestamp, int x, char *message)
{
	char	*tsp;
	char	*index;
	char	*to_write;
	char	*temp;

	index = ft_itoa(x);
	tsp = ft_itoa(timestamp);
	to_write = ft_strjoin(tsp, " ");
	free(tsp);
	temp = ft_strjoin(to_write, index);
	free(index);
	free(to_write);
	to_write = ft_strjoin(temp, message);
	free(temp);
	write(1, to_write, ft_strlen(to_write));
	free(to_write);
}

bool	is_full(t_node *node)
{
	t_info	*info;
	t_philo	*philo;

	philo = node->u_u.philo;
	info = node->info;
	if (atomic_load(&philo->nbr_of_eat) >= info->max_eat)
	{
		info = node->info;
		philo = node->u_u.philo;
		pthread_mutex_lock(&philo->lock_death);
		atomic_store(&philo->is_full, true);
		atomic_fetch_add(&info->nbr_full, 1);
		pthread_mutex_unlock(&philo->lock_death);
		return (true);
	}
	return (false);
}
