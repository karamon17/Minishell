#include "lexer.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	is_neg;

	result = 0;
	is_neg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		is_neg *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	result *= is_neg;
	return (result);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		len;

	len = ft_strlen(s1);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	while (*s1)
		ptr[i++] = *s1++;
	ptr[i] = '\0';
	return (ptr);
}

static int	ft_count(long n)
{
	int	count;

	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*put_int(char *str, int nb, int size, int is_neg)
{
	while (nb > 0)
	{
		*(str + size--) = nb % 10 + '0';
		nb /= 10;
	}
	if (str[1] != '\0' && size == 0 && is_neg == 1)
		*(str + size) = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		is_neg;
	char	*str;
	long	nb;
	size_t	size;

	nb = n;
	if (nb == -2147483648LL)
		return (str = ft_strdup("-2147483648"));
	else if (nb == 0)
		return (str = ft_strdup("0"));
	is_neg = 0;
	size = ft_count(nb);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (nb < 0)
	{
		is_neg = 1;
		nb = nb * -1;
	}
	str[size] = '\0';
	size--;
	put_int(str, nb, size, is_neg);
	return (str);
}