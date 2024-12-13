/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:20:31 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/13 15:19:09 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef enum e_type
{
	PHILO,
	FORK
}	t_type;

typedef	struct s_info
{
	long	nbr_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_eat;
}	t_info;

typedef struct s_fork
{
	bool is_used;
}	t_fork;

typedef struct	s_philo
{
	int	last_eat;
	int	nbr_of_eat;
	int	nbr_of_fork;
}	t_philo;

typedef struct s_node
{
	int		index;
	t_type type;
	union
	{
		t_philo *philo;
		t_fork *fork;
	} u_u;
	struct s_node *next;
	struct s_node *prev;
}	t_node;

t_node	*init(t_info *info, int argc, char **argv);
t_node	*ft_nodelast(t_node *node);
void	verif_errors(char **argv);
int 	ft_usleep(size_t milliseconds);
int		only_digit(char **argv);
long	ft_atol(const char *str);
int		sup_to_maxint(char	**argv);
int		nbr_size(char	*nbr);

#endif