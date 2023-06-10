/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:26:21 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/10 18:29:27 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_path(t_shell *shell, char *str)
{   
    str++;
    str = ft_getenv(shell, str);
    return (str);
}

char    *env_in_DQS(t_shell *shell, char *str)
{
    char    *tmp;
    char    *path;
    int     i;
    int     is_env;

    is_env = 0;
    i = -1;
    tmp = malloc(sizeof(char));
    path = malloc(sizeof(char));
    while (str[++i])
    {
        if (str[i++] == '$')
            is_env = 1;
        while (is_env == 1 && str[i++] != '\0' && str[i] != '"' && str[i] != ' ')
            path = ft_strjoin(path, ft_substr(str, i, 1));
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

t_token *env_check(t_shell *shell, t_token *tokens)
{
    t_token *tmp;

    tmp = tokens;
    while (tmp)
    {
        if (tmp->data[0] == '"')
            tmp->data = env_in_DQS(shell, tmp->data); //check double quotes for ENV and change to variable PATH
		else if (tmp->data[0] == '$' && tmp->data[1] == '?')
        {
			if (shell->err_stat != 0)
			{
				tmp->data = ft_itoa(shell->err_stat);
				shell->err_stat = 0;
			}
			else
				tmp->data = ft_itoa(shell->err_stat);
		}
        else if (tmp->data[0] == '$')
            tmp->data = get_path(shell, tmp->data);  //ENV is not in quotes, so replace var with ENV PATH
        tmp = tmp->next;    //to next node
    }
    // if (quote_check(tokens) == -1)
    // {
    //     free(shell);
    // }
    return (tokens);
}