/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:51:52 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 18:56:43 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_shell *shell, char *str)
{
	str++;
	str = ft_getenv(shell, str);
	return (str);
}

char	*env_in_dqs(t_shell *shell, char *str)
{
	char	*tmp;
	char	*path;
	int		i;
	int		is_env;

	is_env = 0;
	i = -1;
	tmp = ft_calloc(1, sizeof(char));
	path = ft_calloc(1, sizeof(char));
	while (str[++i])
	{
		if (str[i] == '$')
		{
			is_env = 1;
			i++;
		}
		while (is_env == 1 && str[i] != '\0' && str[i] != '"' && str[i] != ' ')
		{
			if (str[i] == '\'')
				break ;
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
		free(path);
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
			tmp->data = env_in_dqs(shell, tmp->data);
		else if (tmp->data[0] == '$')
			tmp->data = get_path(shell, tmp->data);
		tmp = tmp->next;
	}
	return (tokens);
}
