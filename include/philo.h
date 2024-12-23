/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:20:31 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/23 19:35:41 by lgalloux         ###   ########.fr       */
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
# include <stdatomic.h>

typedef enum e_type
{
	PHILO,
	FORK
}	t_type;

typedef enum e_set_or_display
{
	SET,
	DISPLAY
}	t_set_or_display;

typedef struct s_info
{
	int				nbr_of_philo;
	int				max_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	atomic_bool		a_dead;
	atomic_int		nbr_full;
}	t_info;

typedef struct s_fork
{
	pthread_mutex_t	fork_lock;
}	t_fork;

typedef struct s_philo
{
	atomic_int		nbr_of_eat;
	pthread_t		id;
	atomic_int		last_eat;
	atomic_bool		is_full;
	pthread_mutex_t	lock_death;
}	t_philo;

typedef struct s_node
{
	int				index;
	t_type			type;
	t_info			*info;
	union
	{
		t_philo	*philo;
		t_fork	*fork;
	} u_u;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

t_node	*init(t_info *info, int argc, char **argv);
t_node	*ft_nodelast(t_node *node);
t_fork	*ft_forknew(void);
t_node	*ft_nodenew(t_info *info, int index, int type);
void	ft_nodeadd_back(t_node **node, t_node *new, bool is_last);
int		verif_errors(char **argv, int argc);
void	writef(int timestamp, int x, char *message);
void	*philo_life(void *v_node);
void	create_philo(t_node *node);
int		ft_usleep(size_t milliseconds);
bool	is_full(t_node *node);
bool	only_digit(char *arg);
int		ft_atoi(const char *str);
size_t	get_current_time(void);
int		since_start(int set_or_display);
char	*ft_itoa(size_t nbr);
char	*ft_strjoin(const char *str1, const char *str2);
size_t	ft_strlen(char *str);
int		nbr_size(char	*nbr);

#endif