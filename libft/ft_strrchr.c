/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:54:44 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/01/23 17:54:47 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	c1;

	c1 = c;
	i = ft_strlen(s);
	while (i && c1 != s[i])
		i--;
	if (c1 == s[i])
		return ((char *)&(s[i]));
	return (0);
}
