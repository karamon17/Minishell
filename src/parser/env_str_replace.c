/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:51:52 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 17:34:24 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_env(int *i)
{
	(*i)++;
	return (1);
}

static char	*get_path(t_shell *shell, char *str)
{
	str++;
	str = ft_getenv(shell, str);
	return (str);
}

static char	*env_in_dqs(t_shell *shell, char *str, int i, int is_env)
{
	char	*tmp;
	char	*path;

	tmp = malloc(sizeof(char));
	path = malloc(sizeof(char));
	while (str[++i])
	{
		if (str[i] == '$')
			is_env = set_env(&i);
		while (is_env == 1 && str[i] != '\0' && str[i] != '"' && str[i] != ' ')
		{
			path = ft_strjoin(path, ft_substr(str, i, 1));
			i++;
		}
		if ((getenv(path) != NULL) && is_env == 1)
		{
			path = ft_getenv(shell, path);
			tmp = ft_strjoin(tmp, path);
			is_env = 0;
		}
		tmp = ft_strjoin(tmp, ft_substr(str, i, 1));
	}
	return (tmp);
}

t_token	*env_check(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->data[0] == '"')
			tmp->data = env_in_dqs(shell, tmp->data, -1, 0);
		else if (tmp->data[0] == '$')
			tmp->data = get_path(shell, tmp->data);
		tmp = tmp->next;
	}
	return (tokens);
}
