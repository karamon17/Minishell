/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:51:52 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/16 16:57:03 by gkhaishb         ###   ########.fr       */
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
	char	*to_free;
	char	*for_free;

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
			for_free = ft_substr(str, i, 1);
			to_free = path;
			path = ft_strjoin(path, for_free);
			free(for_free);
			free(to_free);
			i++;
		}
		if ((getenv(path) != NULL) && is_env == 1)
		{
			path = ft_getenv(shell, path);
			to_free = tmp;
			tmp = ft_strjoin(tmp, path);
			free(to_free);
			is_env = 0;
		}
		to_free = tmp;
		for_free = ft_substr(str, i, 1);
		tmp = ft_strjoin(tmp, for_free);
		free(for_free);
		free(to_free);
	}
	free(path);
	return (tmp);
}

t_token	*env_check(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;
	t_token	*tmp2;
	char	*to_free;
	char	*for_free;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->data[0] == '"')
			tmp->data = env_in_dqs(shell, tmp->data);
		else if (ft_strchr(tmp->data, '$') && *(ft_strchr(tmp->data, '$') + 1)
			== '?')
		{
			*(ft_strchr(tmp->data, '$')) = 0;
			to_free = ft_itoa(g_error_status);
			for_free = tmp->data;
			tmp->data = ft_strjoin(tmp->data, to_free);
			free(to_free);
			free(for_free);
		}
		else if (ft_strchr(tmp->data, '$') && !ft_strchr(tmp->data, '\''))
		{
			*(ft_strchr(tmp->data, '$')) = 0;
			for_free = tmp->data;
			tmp->data = ft_strjoin(tmp->data, get_path(shell,
						tmp->data + ft_strlen(tmp->data) + 1));
			free(for_free);
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
