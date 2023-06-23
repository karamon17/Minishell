/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:51:52 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/23 15:42:39 by gkhaishb         ###   ########.fr       */
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
		if (str[i] == '$' && str[++i])
			is_env = 1;
		else if (!str[i])
			return (ft_strdup("$"));
		while (is_env == 1 && str[i] && str[i] != '$')
			path = ft_mystrjoin2(path, ft_substr(str, i++, 1));
		if (is_env == 1)
		{
			tmp = ft_mystrjoin2(tmp, ft_getenv(shell, path));
			if (path[0] == '?')
			{
				tmp = ft_mystrjoin2(tmp, ft_itoa(g_error_status));
				tmp = ft_mystrjoin(tmp, path + 1);
			}
			is_env = 0;
			free(path);
			path = ft_calloc(1, sizeof(char));
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
			if (!path[0])
				tmp = ft_strdup("$");
			if (path[0] == '?')
			{
				tmp = ft_mystrjoin2(tmp, ft_itoa(g_error_status));
				tmp = ft_mystrjoin(tmp, path + 1);
			}
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
	int		i;
	char	*prikvel;

	tmp = tokens;
	prikvel = ft_calloc(1, sizeof(char));
	while (tmp)
	{
		i = 0;
		while (tmp->data && tmp->data[i] != '"' && tmp->data[i] != '$')
			i++;
		if (i != 0)
			prikvel = ft_substr(tmp->data, 0, i);
		if (tmp->data && tmp->data[i] == '"')
			tmp->data = ft_mystrjoin2(prikvel, env_in_dqs(shell, tmp->data, i, 0));
		else if (tmp->data && tmp->data[i] == '$')
			tmp->data = ft_mystrjoin2(prikvel, get_path(shell, tmp->data, i, 0));
		tmp = tmp->next;
	}
	return (tokens);
}
