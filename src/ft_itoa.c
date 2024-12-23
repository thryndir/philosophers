/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:12:58 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/23 19:12:59 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*convert(char *str, size_t nbr, int len)
{
	while (len >= 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

int	ft_nbr_count(size_t nbr)
{
	int		len;

	len = 1;
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(size_t nbr)
{
	char	*str;
	int		len;

	len = ft_nbr_count(nbr);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str = convert(str, nbr, len - 1);
	str[len] = '\0';
	return (str);
}
