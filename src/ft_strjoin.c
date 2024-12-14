/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:04:20 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/14 12:28:12 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t ft_strlen(char *str)
{
    size_t len;

    while (str[len])
        len++;
    return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	space_left;
	size_t	i;

	if (dst == NULL || src == NULL)
		return (0);
	destlen = ft_strlen(dst);
	srclen = ft_strlen((const char *)src);
	if (size <= destlen)
		return (size + srclen);
	space_left = size - destlen - 1;
	i = 0;
	while (src[i] != '\0' && i < space_left)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	long unsigned int	i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen((const char *)src));
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*result;
	int		strs_len;
	int		str1_len;
	int		str2_len;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	strs_len = str1_len + str2_len;
	result = malloc((strs_len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, str1, str1_len + 1);
	ft_strlcat(result, str2, strs_len + 1);
	return (result);
}