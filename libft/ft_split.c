/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:54:02 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/01/27 12:54:05 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (j);
}

static char	*ft_putword(const char *s, char c)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		i++;
		j++;
	}
	word = malloc(sizeof(char) * (j + 1));
	if (!word)
		return (0);
	i -= j;
	j = 0;
	while (s[i] && s[i] != c)
		word[j++] = s[i++];
	word[j] = '\0';
	return (word);
}

static void	ft_free(int i, char **new)
{
	while (i > 0)
	{
		free(new[i - 1]);
		i--;
	}
	free(new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		wc;
	int		i;
	int		j;

	if (!s)
		return (0);
	i = -1;
	j = 0;
	wc = ft_wordcount(s, c);
	new = malloc(sizeof(char *) * wc + 1);
	if (!new)
		return (new);
	while (++i < wc)
	{
		while (s[j] && s[j] == c)
			j++;
		new[i] = ft_putword(&s[j], c);
		if (!new[i])
			ft_free(i, new);
		while (s[j] && s[j] != c)
			j++;
	}
	new[i] = 0;
	return (new);
}
