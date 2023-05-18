/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:37 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/15 16:53:39 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

//after first pass check for pipes

char *add_white_space(char *input, int j)
{
    char *tmp;

    tmp = (char *)malloc(sizeof(char));
    tmp = "";
    while (input[j])
    {
        if (input[j] == '|')
            tmp = double_strjoin(tmp, input, &j);
        if ((input[j] == '<' && input[j + 1] != '<') || (input[j] == '>' && input[j + 1] != '>'))
            tmp = double_strjoin(tmp, input, &j);
        else if ((input[j] == '<' && input[j - 1] == '<') || (input[j] == '>' && input[j - 1] == '>'))
            tmp = double_strjoin(tmp, input, &j);
        tmp = ft_strjoin(tmp, ft_substr(input, j, 1));
        j++;
    }
    return (tmp);
}

int d_quotes(char *input, int i, t_token **new)
{
    while (input[i] != '"' && input[i] != '\0')
    {
       (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    if (input[i] != '\0')
         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
    (*new)->type = TEXT;
    return (i);
}

int append_word(char *input, int i, t_token **new)
{
    while (input[i] != ' ' && input[i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    (*new)->type = TEXT;
    return (i);
}

int s_quotes(char *input, int i, t_token **new)
{
    while (input[i] != '\'' && input[i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    if (input[i] != '\0')
         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
    if (ft_strcmp((*new)->data, "$"))
        (*new)->type = ENV;
    else
        (*new)->type = TEXT;
    return (i);
}

t_token    *first_parse(char *input, t_token *tokens)
{
    t_token *new;
    int     i;
    int     j;
    char    *tmp;

    i = 0;
    j = 0;
    tmp = add_white_space(input, j);
    while (tmp[i] == ' ' && tmp[i])
        i++;
    while (tmp[i])
    {
        new = ft_new_token(ft_substr(tmp, i, 1));
        if (tmp[i] == '\'')
            i = s_quotes(tmp, i + 1, &new);
        else if (tmp[i] == '"')
            i = d_quotes(input, i + 1, &new);
        else if (tmp[i] != ' ')
           i = append_word(tmp, i + 1, &new);
        ft_token_add_back(&tokens, new);
        i++;
    }
    second_parse(&tokens);
    while (tokens != NULL)
    {
        printf("{%s}\n", tokens->data);
        printf("[%d]\n", tokens->type);
        tokens = tokens->next;
    }
    return (tokens);
}
