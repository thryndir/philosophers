/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:20:31 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/17 18:22:24 by lgalloux         ###   ########.fr       */
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
# include <string.h>

typedef enum e_type
{
	PHILO,
	FORK
}	t_type;

typedef	struct s_info
{
	int				nbr_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				max_eat;
	bool			a_dead;
	struct s_node	*node;
}	t_info;

typedef struct s_fork
{
	pthread_mutex_t fork_lock;
	bool 			is_used;
}	t_fork;

typedef struct	s_philo
{
	pthread_t	id;
	size_t		last_eat;
	int			nbr_of_eat;
	int			nbr_of_fork;
	bool		is_dead;
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
void	print_node(t_node *node);
void	verif_errors(char **argv);
void	writef(size_t timestamp, int x, char *message);
void	create_philo(t_info info);
int 	ft_usleep(size_t milliseconds);
int		only_digit(char **argv);
long	ft_atol(const char *str);
size_t	get_current_time(void);
char	*ft_itoa(size_t nbr);
char	*ft_strjoin(const char *str1, const char *str2);
size_t	ft_strlen(char *str);
int		sup_to_maxint(char	**argv);
int		nbr_size(char	*nbr);

#endif