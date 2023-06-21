/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:51:52 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/19 19:45:59 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_shell *shell, char *str)
{
	str++;
	str = ft_getenv(shell, str);
	return (str);
}

char *env_in_dqs(t_shell *shell, char *str, int i, int is_env)
{
    char *tmp;
    char *path;
    char *env_value;

    tmp = ft_calloc(1, sizeof(char));
    path = ft_calloc(1, sizeof(char));
    while (str[i])
    {
        if (str[i] == '$')
        {
            is_env = 1;
            i++;
        }
        while (is_env == 1 && str[i] != '\0' && str[i] != '"' && str[i] != ' ' && str[i] != '$' && str[i] != '\'')
        {
            path = ft_strjoin(path, ft_substr(str, i, 1));
            i++;
        }
        if (is_env == 1)
        {
            env_value = ft_getenv(shell, path);
            tmp = ft_strjoin(tmp, env_value != NULL ? env_value : "");
            is_env = 0;
            path = ft_strdup("");
        }
        if (str[i] != '\0')
        {
            if (str[i] == '$')
                continue ;
            tmp = ft_strjoin(tmp, ft_substr(str, i, 1));
            i++;
        }
    }
    free(path);
    return tmp;
}

t_token	*env_check(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->data[0] == '"')
			tmp->data = env_in_dqs(shell, tmp->data, 0, 0);
		else if (tmp->data[0] == '$')
			tmp->data = get_path(shell, tmp->data);
		tmp = tmp->next;
	}
	return (tokens);
}
