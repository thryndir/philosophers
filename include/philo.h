/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:20:31 by thryndir          #+#    #+#             */
/*   Updated: 2024/06/09 22:44:38 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

struct s_philo
{
	pthread_t	*threads;
	int			*forks;
	int			nbr_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_of_eat;

} typedef t_philo;

void 	init(t_philo *philo, char **argv, int argc);
void	verif_errors(char **argv);
int 	ft_usleep(size_t milliseconds);
int		only_digit(char **argv);
int		ft_atoll(const char *str);
int		sup_to_maxint(char	**argv);
int		nbr_size(char	*nbr);

#endif