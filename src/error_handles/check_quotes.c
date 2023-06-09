/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:55:29 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/09 14:55:30 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    count_quotes(char type, char *str)
{
    int cnt;
    int i;

    cnt = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == type)
            cnt++;
        i++;
    }
    if (cnt % 2 != 0)
    {
        printf("QUOTE ERROR IN COUNT");
        exit(1);
    }
}

char    set_quote_type(char *str)
{
    int     i;
    char    fnd;
    int     cnt;

    i = 0;
    cnt = 0;
    if (str[0] == '\'')
        printf("waht the fuck");
    while (str[i] != '\'' && str[i] != '"' && str[i])
        i++;
    if (str[i] == '\'' || str[i] == '"')
    {
        fnd = str[i];
        cnt++;
    }
    i++;
    while (str[i] && str[i] != fnd)
        i++;
    if (str[i] == fnd && fnd != '\0')
        cnt++;
    printf("[%d]\n", cnt);
    if (cnt % 2 != 0 && cnt != 0)
    {
        printf("QUOTE ERROR");
        exit(1);
    }
    if (fnd == '\'')
        return ('\'');
    else if (fnd == '"')
        return ('"');
    return ('\0');
}

int     quote_check(t_token *tokens)
{
    t_token *tmp;
    tmp = tokens;
    while (tmp)
    {
        tmp->type = set_quote_type(tmp->data);
        count_quotes(tmp->type, tmp->data);
        tmp = tmp->next;
    }
    return (0);
}
