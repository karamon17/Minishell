/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:37 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/23 12:01:55 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_white_space(char *input, int j, int size, int in_q)
{
	char	*tmp;

	while (input[j])
		size = white_space_helper(input, j++, in_q, size);
	tmp = ft_calloc(size + 1, sizeof(char));
	j = -1;
	while (input[++j])
	{
		if (!in_q && (input[j] == '|' || input[j] == '<' || input[j] == '>'))
			tmp = set_tmp(input, j, tmp);
		else if (input[j] == '"' || input[j] == '\'')
		{
			in_q = update_in_q(tmp, j, in_q);
			tmp = ft_mystrjoin2(tmp, ft_substr(input, j, 1));
			// if ((input[j] == '"' && input[j + 1] == '\'')
			// 	|| (input[j] == '\'' && input[j + 1] == '"'))
			// 	tmp = ft_mystrjoin(tmp, " ");
		}
		else
			tmp = ft_mystrjoin2(tmp, ft_substr(input, j, 1));
	}
	free(input);
	return (tmp);
}

int	d_quotes(char *input, int i, t_token **new)
{
	while ((input[i] != '\0'))
	{
		(*new)->data = ft_mystrjoin2((*new)->data, ft_substr(input, i++, 1));
		if (input[i] == '"' && (input[i + 1] == ' ' || input[i + 1] == '\0'))
			break ;
	}
	if (input[i] != '\0')
		(*new)->data = ft_mystrjoin2((*new)->data, ft_substr(input, i, 1));
	return (i);
}

int	append_word(char *input, int i, t_token **new)
{
	while (input[i] != ' ' && input[i] != '\0')
		(*new)->data = ft_mystrjoin2((*new)->data, ft_substr(input, i++, 1));
	return (i);
}

int	s_quotes(char *input, int i, t_token **new)
{
	while ((input[i] != '\0'))
	{
		(*new)->data = ft_mystrjoin2((*new)->data, ft_substr(input, i++, 1));
		if (input[i] == '\'' && (input[i + 1] == ' ' || input[i + 1] == '\0'))
			break ;
	}
	if (input[i] != '\0')
		(*new)->data = ft_mystrjoin2((*new)->data, ft_substr(input, i, 1));
	return (i);
}

t_token	*first_parse(char *tmp, t_shell *shell, int i)
{
	int		check;
	t_token	*new;

	check = 0;
	tmp = add_white_space(tmp, 0, 0, 0);
	while (tmp[i] == ' ' && tmp[i])
		i++;
	while (tmp[i])
	{
		new = ft_new_token(ft_substr(tmp, i, 1));
		if (!new)
			break ;
		i = parse_norm_helper(tmp, new, i);
		if (new->data[0] && check++ > 0)
			ft_token_add_back(&shell->tokens, new);
		else if (new->data[0])
			shell->tokens = new;
		if (tmp[i])
			i++;
	}
	free(tmp);
	if (quote_check(shell->tokens) == -1)
		return (shell->tokens);
	return (cut_spaces(&shell->tokens), shell->tokens);
}
