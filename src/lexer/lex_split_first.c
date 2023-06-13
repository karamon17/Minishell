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

char *add_space(char *input, int j)
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
            {
                if (!(input[j] == '<' && input[j - 1] == '<') || (input[j] == '>' && input[j - 1] == '>'))
                    tmp = ft_strjoin(tmp, " ");
            }
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

int		append_word(char *str, int i, t_token **new)
{
	while (str[i] != ' ' && str[i])
	{
		(*new)->data = ft_strjoin((*new)->data, ft_substr(str, i, 1));
		i++;
	}
	return (i);
}

int		redirects(char *str, int i, t_token **new)
{
	while (str[i])
	{
		(*new)->data = ft_strjoin((*new)->data, ft_substr(str, i, 1));
		i++;
		if (str[i] == '|' && (str[i + 1] == ' ' || str[i + 1]))
			break ;
		else if (str[i] == '<' && (str[i + 1] == ' ' || str[i + 1]))
			break ;
		else if (str[i] == '>' && (str[i + 1] == ' ' || str[i = 1]))
			break;
	}
	if (str[i])
		(*new)->data = ft_strjoin((*new)->data, ft_substr(str, i, 1));
	return (i);
}

int		d_quotes(char *str, int i, t_token **new)
{
	while (str[i])
	{
		(*new)->data = ft_strjoin((*new)->data, ft_substr(str, i, 1));
		i++;
		if (str[i] == '"' && (str[i + 1] == ' ' || str[i + 1]))
			break ;
	}
	if (str[i] != '\0')
		(*new)->data = ft_strjoin((*new)->data, ft_substr(str, i, 1));
	return (i);
}

int		s_quotes(char *str, int i, t_token **new)
{
	while (str[i])
	{
		(*new)->data = ft_strjoin((*new)->data, ft_substr(str, i, 1));
		i++;
		if (str[i] == '\'' && (str[i + 1] == ' ' || str[i + 1]))
			break ;
	}
	if (str[i] != '\0')
		(*new)->data = ft_strjoin((*new)->data, ft_substr(str, i, 1));
	return (i);
}

t_token	*first_parse(t_shell *shell, char *input, int i)
{
	t_token	*new;

	input = add_space(input, 0);
	while (input[i] == ' ' && input[i])
		i++;
	while (input[i])
	{
		new = ft_new_token(ft_substr(input, i, 1));
		if (input[i] == '\'')
			i = s_quotes(input, i + 1, &new);
		else if (input[i] == '"')
			i = d_quotes(input, i + 1, &new);
		else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			i = redirects(input, i + 1, &new);
		else if (input[i] != ' ')
			i = append_word(input, i + 1, &new);
        if (!shell->tokens->data)
            shell->tokens = new;
        else
            ft_token_add_back(&shell->tokens, new);
        if (input[i] == '\0')
            continue ;
		i++;
	}
	if (quote_check(shell->tokens) == -1)
	{
		shell->err_stat = -1;
		free_shell(&shell);
	}
	cut_spaces(&shell->tokens);
	return (shell->tokens);
}
