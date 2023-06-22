/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:51:52 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/22 14:30:40 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_shell *shell, char *str, int i, int is_env)
{
	char	*tmp;
	char	*path;

	tmp = ft_calloc(1, sizeof(char));
	path = ft_calloc(1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '$' && str[i++])
			is_env = 1;
		while (is_env == 1 && str[i] && str[i] != '$')
			path = ft_mystrjoin2(path, ft_substr(str, i++, 1));
		if (is_env == 1)
		{
			tmp = ft_mystrjoin2(tmp, ft_getenv(shell, path));
			is_env = 0;
			free(path);
			path = ft_strdup("");
		}
		if (str[i] && str[i] != '$')
			tmp = ft_mystrjoin2(tmp, ft_substr(str, i++, 1));
	}
	free(str);
	free(path);
	return (tmp);
}

char	*env_in_dqs(t_shell *shell, char *str, int i, int is_env)
{
	char	*tmp;
	char	*path;

	tmp = ft_calloc(1, sizeof(char));
	path = ft_calloc(1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '$' && str[i++])
			is_env = 1;
		while (is_env == 1 && str[i] != '\0' && str[i] != '"' && str[i] != ' '
			&& str[i] != '$' && str[i] != '\'')
			path = ft_mystrjoin2(path, ft_substr(str, i++, 1));
		if (is_env == 1)
		{
			tmp = ft_mystrjoin2(tmp, ft_getenv(shell, path));
			is_env = 0;
			free(path);
			path = ft_strdup("");
		}
		if (str[i] && str[i] != '$')
			tmp = ft_mystrjoin2(tmp, ft_substr(str, i++, 1));
	}
	free(str);
	free(path);
	return (tmp);
}

t_token	*env_check(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->data && tmp->data[0] == '"')
			tmp->data = env_in_dqs(shell, tmp->data, 0, 0);
		else if (ft_strchr(tmp->data, '$') && *(ft_strchr(tmp->data, '$') + 1)
			== '?')
		{
			*(ft_strchr(tmp->data, '$')) = 0;
			tmp->data = ft_mystrjoin2(tmp->data, ft_itoa(g_error_status));
		}
		else if (tmp->data && tmp->data[0] == '$')
			tmp->data = get_path(shell, tmp->data, 0, 0);
		tmp = tmp->next;
	}
	return (tokens);
}
