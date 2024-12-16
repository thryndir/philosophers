#include "philo.h"

char	*convert(char *str, int nbr, int len)
{
	long l_nbr;

	l_nbr = nbr;
	if (l_nbr < 0)
	{
		str[0] = '-';
		l_nbr *= -1;
	}
	while (len > 0)
	{
		str[len] = l_nbr % 10 + '0';
		l_nbr = l_nbr / 10;
		len--;
	}
	return (str);
}

int	ft_nbr_count(int nbr)
{
	int		len;
	long	l_nbr;

	len = 1;
	l_nbr = nbr;
	if (l_nbr < 0)
	{
		l_nbr *= -1;
		len++;
	}
	while (l_nbr >= 10)
	{
		l_nbr = l_nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		len;

	len = ft_nbr_count(nbr);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str = convert(str, nbr, len);
	str[len + 1] = '\0';
	return (str);
}
