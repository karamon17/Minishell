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
    return (tmp);
}

t_token *env_check(t_shell *shell, t_token *tokens)
{
    printf("%s\n", tokens->data);
    t_token *tmp;

    tmp = tokens;
    while (tmp)
    {
        if (tmp->data[0] == '"')
            tmp->data = env_in_DQS(shell, tmp->data); //check double quotes for ENV and change to variable PATH
        else if (tmp->data[0] == '$')
            tmp->data = get_path(shell, tmp->data);  //ENV is not in quotes, so replace var with ENV PATH
        tmp = tmp->next;    //to next node
    }
    printf("[%s]\n", tokens->data);
    if (quote_check(tokens) == -1)
    {
        printf("ashahatoom");
        free(shell);
    }
    return (tokens);
}
