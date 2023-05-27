/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:51:39 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/01/28 19:51:41 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_check(long nb, char *str, int i)
{
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0 && i >= 0)
	{
		str[i] = '0' + (nb % 10);
		nb = nb / 10;
		i--;
	}
	return (str);
}

static int	ft_lenght(long nb)
{
	long	len;

	len = 0;
	if (nb == 0)
		len = 1;
	while (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		i;

	nb = n;
	i = ft_lenght(nb);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	if (nb == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return (str);
	}
	str[i--] = 0;
	return (ft_check(nb, str, i));
}
