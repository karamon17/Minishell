/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:02:11 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/27 14:02:13 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_single_quotes(t_shell *shell, char *str, int *k)
{
	char	*in_quotes;
	int		i;

	(void)shell;
	i = *k;
	in_quotes = ft_substr(str, i++, 1);
	while (str[i] && str[i] != '\'')
	{
		in_quotes = ft_mystrjoin2(in_quotes, ft_substr(str, i++, 1));
	}
	if (str[i] == '\'')
		in_quotes = ft_mystrjoin2(in_quotes, ft_substr(str, i++, 1));
	*k = i;
	return (in_quotes);
}

char	*quotes_help(char *in_quotes, t_shell *shell, char **path, int *is_env)
{
	in_quotes = ft_mystrjoin2(in_quotes, ft_getenv(shell, *path));
	if (!*path[0])
		in_quotes = helper(in_quotes);
	if (*path[0] == '?')
	{
		in_quotes = ft_mystrjoin2(in_quotes, ft_itoa(g_error_status));
		in_quotes = ft_mystrjoin(in_quotes, *path + 1);
	}
	*is_env = 0;
	free(*path);
	*path = ft_strdup("");
	return (in_quotes);
}

char	*ft_double_quotes(t_shell *shell, char *str, int *k)
{
	char	*in_quotes;
	char	*path;
	int		is_env;

	in_quotes = ft_substr(str, (*k)++, 1);
	path = ft_calloc(1, sizeof(char));
	is_env = 0;
	while (str[*k] && str[*k] != '"')
	{
		if (str[*k] == '$' && str[(*k)++])
			is_env = 1;
		while (is_env == 1 && str[*k] && str[*k] != '"' && str[*k] != ' ' && \
		str[*k] != '$' && str[*k] != '\'' && str[*k] != '/' && str[*k] != '=')
			path = ft_mystrjoin2(path, ft_substr(str, (*k)++, 1));
		if (is_env == 1)
			in_quotes = quotes_help(in_quotes, shell, &path, &is_env);
		else
			in_quotes = ft_mystrjoin2(in_quotes, ft_substr(str, (*k)++, 1));
	}
	if (str[*k] == '"')
		in_quotes = ft_mystrjoin2(in_quotes, ft_substr(str, (*k)++, 1));
	free(path);
	return (in_quotes);
}

char	*env_check_help(t_shell *shell, char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_calloc(1, sizeof(char));
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '$' && str[i] != '\'')
		{
			new_str = ft_mystrjoin2(new_str, ft_substr(str, i, 1));
			i++;
		}
		else if (str[i] == '"')
			new_str = ft_mystrjoin2(new_str, ft_double_quotes(shell, str, &i));
		else if (str[i] == '\'')
			new_str = ft_mystrjoin2(new_str, ft_single_quotes(shell, str, &i));
		else if (str[i] == '$')
			new_str = ft_mystrjoin2(new_str, ft_get_value(shell, str, &i));
	}
	free(str);
	return (new_str);
}

t_token	*env_check(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	(void)shell;
	while (tmp)
	{
		tmp->data = env_check_help(shell, tmp->data);
		tmp = tmp->next;
	}
	return (tokens);
}
