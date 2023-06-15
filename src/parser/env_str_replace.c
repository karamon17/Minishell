/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:51:52 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/15 15:08:00 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_shell *shell, char *str)
{
	char	*tmp;
	char	*new;
	char	*fromenv;

	tmp = ft_strchr(str, '/');
	if (!tmp)
		str = ft_getenv(shell, str);
	else
	{
		new = ft_substr(str, 0, tmp - str);
		fromenv = ft_getenv(shell, new);
		if (!fromenv)
			fromenv = ft_calloc(1, sizeof(char));
		str = ft_strjoin(fromenv, tmp);
	}
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
	free(path);
	return (tmp);
}

t_token	*env_check(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;
	t_token	*tmp2;
	//char **variables;

	tmp = tokens;
	while (tmp)
	{
		//variables = ft_split(tmp->data)
		if (tmp->data[0] == '"')
			tmp->data = env_in_dqs(shell, tmp->data);
		else if (ft_strchr(tmp->data, '$') && *(ft_strchr(tmp->data, '$') + 1)
			== '?')
		{
			*(ft_strchr(tmp->data, '$')) = 0;
			tmp->data = ft_strjoin(tmp->data, ft_itoa(g_error_status));
		}
		else if (ft_strchr(tmp->data, '$'))
		{
			*(ft_strchr(tmp->data, '$')) = 0;
			tmp->data = ft_strjoin(tmp->data, get_path(shell,
						tmp->data + ft_strlen(tmp->data) + 1));
		}
		if (!tmp->data)
		{	
			tmp2 = tmp->next;
			delete_token(&shell->tokens, tmp);
			tmp = tmp2;
		}
		else
			tmp = tmp->next;
	}
	return (tokens);
}
