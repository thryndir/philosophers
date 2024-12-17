#include "philo.h"

char	*convert(char *str, size_t nbr, int len)
{
	if (nbr < 0)
		str[0] = '-';
	while ((len > 0 && nbr < 0) || (len >= 0 && nbr >= 0))
	{
		str[len] = (nbr % 10) * (1 - 2 * (nbr < 0)) + '0';
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
