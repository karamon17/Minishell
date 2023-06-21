/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:37 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/20 13:24:26 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *add_white_space(char *input, int j, int size, int in_q)
{
    char *tmp;
    char *to_free;
    char *for_free;

    while (input[j])
    {
        size = white_space_helper(input, j, in_q, size);
        j++;
    }
    tmp = ft_calloc(size + 1, sizeof(char));
    j = 0;
    while (input[j])
    {
        if (!in_q && (input[j] == '|' || input[j] == '<' || input[j] == '>'))
        {
            tmp = set_tmp(input, j, tmp);
        }
        else if (input[j] == '"' || input[j] == '\'')
        {
            in_q = update_in_q(tmp, j, in_q);
            to_free = tmp;
            for_free = ft_substr(input, j, 1);
            tmp = ft_strjoin(tmp, for_free);
            free(to_free);
            free(for_free);
            if ((input[j] == '"' && input[j + 1] == '\'') || (input[j] == '\'' && input[j + 1] == '"'))
                tmp = ft_strjoin(tmp, " ");
        }
        else
        {
            to_free = tmp;
            for_free = ft_substr(input, j, 1);
            tmp = ft_strjoin(tmp, for_free);
            free(to_free);
            free(for_free);
        }
        j++;
    }
    return tmp;
}


int	d_quotes(char *input, int i, t_token **new)
{
	char	*for_free;
	char	*to_free;

	while ((input[i] != '\0'))
	{
		for_free = ft_substr(input, i, 1);
		to_free = (*new)->data;
		(*new)->data = ft_strjoin(to_free, for_free);
		free(for_free);
		free(to_free);
		i++;
		if (input[i] == '"' && (input[i + 1] == ' ' || input[i + 1] == '\0'))
			break ;
	}
	if (input[i] != '\0')
	{
		for_free = ft_substr(input, i, 1);
		to_free = (*new)->data;
		(*new)->data = ft_strjoin(to_free, for_free);
		free(for_free);
		free(to_free);
	}
	return (i);
}

int	append_word(char *input, int i, t_token **new)
{
	char	*for_free;
	char	*to_free;

	while (input[i] != ' ' && input[i] != '\0')
	{
		for_free = ft_substr(input, i, 1);
		to_free = (*new)->data;
		(*new)->data = ft_strjoin(to_free, for_free);
		free(for_free);
		free(to_free);
		i++;
	}
	return (i);
}

int	s_quotes(char *input, int i, t_token **new)
{
	char	*for_free;
	char	*to_free;

	while ((input[i] != '\0'))
	{
		to_free = (*new)->data;
		for_free = ft_substr(input, i, 1);
		(*new)->data = ft_strjoin(to_free, for_free);
		free(for_free);
		free(to_free);
		i++;
		if (input[i] == '\'' && (input[i + 1] == ' ' || input[i + 1] == '\0'))
			break ;
	}
	if (input[i] != '\0')
	{
		to_free = (*new)->data;
		for_free = ft_substr(input, i, 1);
		(*new)->data = ft_strjoin(to_free, for_free);
		free(for_free);
		free(to_free);
	}
	return (i);
}

t_token	*first_parse(char *tmp, t_shell *shell, int i)
{
	int		check;
	char	*to_free;
	t_token	*new;

	check = 0;
	to_free = tmp;
	tmp = add_white_space(tmp, 0, 0, 0);
	free(to_free);
	while (tmp[i] == ' ' && tmp[i])
		i++;
	while (tmp[i])
	{
		new = ft_new_token(ft_substr(tmp, i, 1));
		if (!new)
			break ;
		i = parse_norm_helper(tmp, new, i);
		if (new->data[0] != '\0')
		{
			if (check > 0)
				ft_token_add_back(&shell->tokens, new);
			else
				shell->tokens = new;
			check++;
		}
		if (tmp[i])
			i++;
	}
	free(tmp);
	if (quote_check(shell->tokens) == -1)
		return (shell->tokens);
	cut_spaces(&shell->tokens);
	return (shell->tokens);
}
