#include "philo.h"

char	*convert(char *str, int nbr, int len)
{
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (len > 0)
	{
		str[len] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

int	ft_nbr_count(int nbr)
{
	int	len;

	len = 1;
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		len;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_nbr_count(nbr);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str = convert(str, nbr, len);
	str[len + 1] = '\0';
	return (str);
}
