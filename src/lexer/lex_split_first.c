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

# include "minishell.h"

//after first pass check for pipes

void    cut_spaces(t_token **tokens)
{
    t_token *tmp;
    t_token *tmp2;

    tmp = (*tokens);
    tmp2 = tmp;
    while (tmp)
    {
        if (tmp->data[0] == ' ')
            delete_token(tokens, tmp);
        tmp = tmp->next;
    }
}

char *add_white_space(char *input, int j)
{
    char *tmp;
    int tmp_size;
    int in_quotes;

    tmp_size = 0;
    in_quotes = 0;
    while (input[j])
    {
        if (!in_quotes && (input[j] == '|' || input[j] == '<' || input[j] == '>'))
        {
            if (input[j - 1] != ' ')
                tmp_size++;
            tmp_size++;
            if (input[j + 1] != ' ' && input[j + 1] != input[j])
                tmp_size++;
        }
        else if (input[j] == '"' || input[j] == '\'')
        {
            if (in_quotes && input[j] == in_quotes)
                in_quotes = 0;
            else if (!in_quotes)
                in_quotes = input[j];
        }
        tmp_size++;
        j++;
    }

    tmp = (char *)malloc((tmp_size + 1) * sizeof(char));
    if (!tmp)
        return NULL;
    tmp[0] = '\0';
    j = 0;

    while (input[j])
    {
        if (!in_quotes && (input[j] == '|' || input[j] == '<' || input[j] == '>'))
        {
            if (input[j - 1] != ' ')
                tmp = ft_strjoin(tmp, " ");
            tmp = ft_strjoin(tmp, ft_substr(input, j, 1));
            if (input[j + 1] != ' ' && input[j + 1] != input[j])
                tmp = ft_strjoin(tmp, " ");
        }
        else if (input[j] == '"' || input[j] == '\'')
        {
            if (in_quotes && input[j] == in_quotes)
                in_quotes = 0;
            else if (!in_quotes)
                in_quotes = input[j];
            tmp = ft_strjoin(tmp, ft_substr(input, j, 1));
        }
        else
            tmp = ft_strjoin(tmp, ft_substr(input, j, 1));
        j++;
    }

    return tmp;
}

int d_quotes(char *input, int i, t_token **new)
{
    while ((input[i] != '\0')) //aaaaaaaaa || input[i] != ' '
    {
       (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
        if (input[i] == '"' && (input[i + 1] == ' ' || input[i + 1] == '\0'))
        {
            (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
            break;
        }
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
    while (input[i] != '\'' && input[i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        if (input[i] == '\'' && (input[i + 1] == ' ' || input[i + 1] == '\0'))
        {
            (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
            break;
        }
        i++;
    }
    if (input[i] != '\0')
         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
    return (i);
}

int is_special_token(char *token) 
{
    return ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0;
}

t_token *first_parse(char *input, t_token *tokens) 
{
    int check = 0;
    t_token *new;
    int i = 0;
    int j = 0;
    char *tmp;

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
        else if (tmp[i] == ' ') 
        {
            while (tmp[i + 1] == ' ') 
                i++;
        }
        if (new->data[0] != '\0') 
        {
            if (check > 0) 
            {
                if (is_special_token(new->data) && ft_strcmp(tokens->data, "|") != 0) 
                {
                    t_token *last_token = ft_token_last(tokens);
                    if (last_token && ft_strcmp(last_token->data, " ") != 0) 
                    {
                        t_token *space_token = ft_new_token(" ");
                        ft_token_add_back(&tokens, space_token);
                    }
                }
                ft_token_add_back(&tokens, new);
            } 
            else
                tokens = new;
            check++;
        }
        i++;
    }
    cut_spaces(&tokens);
    return tokens;
}

// ինչպես կանմե այն?
// յետ է ունեմ "abcd""qrst", պետկե նաշանակէ abcdqrst մեկ տոկեն մեչ
// յետ է ունեմ "a"bc"d", պետկե նաշանակէ abcd մեկ տոկեն մեչ
// եվ, յետ է ունեմ "աբ'սդ", պետկե նաշանակէ աբ'սդ արրանծ "".

// Առաչին, պետկե ստուգեմ յետ է whitespace կա արաչ եվ հեդո ""/''
// յետ Ե վոչ, դնել quotes մեկ նոդ մեչ