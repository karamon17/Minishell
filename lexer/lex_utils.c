/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:43 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/15 16:53:45 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2 && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	cnt;

	cnt = 0;
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)malloc ((sizeof(char) * (len + 1)));
	if (!sub)
		return (0);
	while (cnt < len)
	{
		sub[cnt] = s[start + cnt];
		cnt++;
	}
	sub[cnt] = '\0';
	return (sub);
}

size_t  ft_strlen(const char *str)
{
    size_t  i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*double_strjoin(char *tmp, char *input, int *j)
{
	tmp = ft_strjoin(tmp, ft_substr(input, *j, 1));
    tmp = ft_strjoin(tmp, " ");
	(*j)++;
	return (tmp);
}
