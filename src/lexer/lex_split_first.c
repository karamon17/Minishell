/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:37 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/08 20:00:07 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char *add_white_space(char *input, int j, int size, int in_q)
{
    char *tmp;

    while (input[j])
    {
        size = white_space_helper(input, j, in_q, size);
        j++;
    }
    tmp = allocate_and_check_tmp(size);
    j = 0;
    while (input[j])
    {
        if (!in_q && (input[j] == '|' || input[j] == '<' || input[j] == '>'))
            tmp = set_tmp(input, j, tmp);
        else if (input[j] == '"' || input[j] == '\'')
        {
            in_q = update_in_q(tmp, j, in_q);
            tmp = ft_strjoin(tmp, ft_substr(input, j, 1));
        }
        else
            tmp = ft_strjoin(tmp, ft_substr(input, j, 1));
        j++;
    }
    return (tmp);
}

int d_quotes(char *input, int i, t_token **new)
{
    while ((input[i] != '\0'))
    {
       (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
        if (input[i] == '"' && (input[i + 1] == ' ' || input[i + 1] == '\0'))
            break ;
    }
    if (input[i] != '\0')
         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
    return (i);
}

int append_word(char *input, int i, t_token **new)
{
    while (input[i] != ' ' && input[i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    return (i);
}

int s_quotes(char *input, int i, t_token **new)
{
    while ((input[i] != '\0'))
    {
       (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
        if (input[i] == '\'' && (input[i + 1] == ' ' || input[i + 1] == '\0'))
            break ;
    }
    if (input[i] != '\0')
         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
    return (i);
}

t_token *first_parse(char *tmp, t_shell *shell, int i)
{
    int     check;
    t_token *new;

    check = 0;
    tmp = add_white_space(tmp, 0, 0, 0);
    while (tmp[i] == ' ' && tmp[i]) 
        i++;
    while (tmp[i]) 
    {
        new = ft_new_token(ft_substr(tmp, i, 1));
        i = parse_norm_helper(tmp, new, i);
        if (new->data[0] != '\0') 
        {
            if (check > 0) 
                ft_token_add_back(&shell->tokens, new);
            else
                shell->tokens = new;
            check++;
        }
        i++;
    }
    if (quote_check(shell->tokens) == -1)
        clean_shell(&shell);
    cut_spaces(&shell->tokens);
    return (shell->tokens);
}