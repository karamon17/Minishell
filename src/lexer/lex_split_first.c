/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:00:36 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/27 14:00:37 by jfrances         ###   ########.fr       */
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
		}
		else
			tmp = ft_mystrjoin2(tmp, ft_substr(input, j, 1));
	}
	free(input);
	return (tmp);
}

int	d_quotes(char *input, int i, t_token **new)
{
	int	flag;

	flag = 0;
	while ((input[i] != '\0'))
	{
		(*new)->data = ft_mystrjoin2((*new)->data, ft_substr(input, i++, 1));
		if (input[i] == '"')
			flag = 1;
		if (flag && (input[i] == ' ' || input[i] == '\0'))
			break ;
	}
	if (input[i] != '\0')
		(*new)->data = ft_mystrjoin2((*new)->data, NULL);
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
	int	flag;

	flag = 0;
	while ((input[i] != '\0'))
	{
		(*new)->data = ft_mystrjoin2((*new)->data, ft_substr(input, i++, 1));
		if (input[i - 1] == '\'')
			flag = 1;
		if (flag && (input[i] == ' ' || input[i] == '\0'))
			break ;
	}
	if (input[i] != '\0' && input[i] != ' ')
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
	shell->tokens = check_redirects(shell->tokens);
	if (error_in_tokens(&shell) == -1 || quote_check(shell->tokens) == -1)
		return ((shell->tokens));
	return (cut_spaces(&shell->tokens), shell->tokens);
}
