/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:26:21 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/29 12:26:22 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_path(t_shell *shl)
{   
    shl->tokens->data++;
    shl->tokens->data = ft_getenv(shl, shl->tokens->data);
    return (shl->tokens->data);
}

char    *env_in_DQS(t_shell *shl)
{
    char    *tmp;
    char    *path;
    int     i;
    int     is_env;

    is_env = 0;
    i = -1;
    tmp = malloc(sizeof(char));
    path = malloc(sizeof(char));
    while (shl->tokens->data[++i])
    {
        if (shl->tokens->data[i] == '$')
        {
            is_env = 1;
            i++;
        }
        while (is_env == 1 && shl->tokens->data[i] != '\0' && shl->tokens->data[i] != '"' && shl->tokens->data[i] != ' ')
        {
            path = ft_strjoin(path, ft_substr(shl->tokens->data, i, 1));
            i++;
        }
        if ((ft_getenv(shl, path) != NULL) && is_env == 1)
        {
            path = ft_getenv(shl, path);
            tmp = ft_strjoin(tmp, path);
            is_env = 0;
        }
        tmp = ft_strjoin(tmp, ft_substr(shl->tokens->data, i, 1));
    }
    return (tmp);
}

t_token *env_check(t_shell *shell)
{
    t_shell *tmp;

    tmp = shell;
    while (tmp->tokens)
    {
        if (tmp->tokens->data[0] == '"')
            tmp->tokens->data = env_in_DQS(tmp); //check double quotes for ENV and change to variable PATH
        else if (tmp->tokens->data[0] == '$')
            tmp->tokens->data = get_path(tmp);  //ENV is not in quotes, so replace var with ENV PATH
        tmp->tokens = tmp->tokens->next;    //to next node
    }
    return (tmp->tokens);
}
