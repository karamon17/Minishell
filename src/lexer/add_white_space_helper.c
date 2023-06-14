/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_white_space_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:54:52 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 16:58:29 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	white_space_helper(char *input, int j, int in_q, int size)
{
	if (!in_q && (input[j] == '|' || input[j] == '<' || input[j] == '>'))
	{
		if (input[j - 1] != ' ')
			size++;
		size++;
		if (input[j + 1] != ' ' && input[j + 1] != input[j])
		size++;
	}
	else if (input[j] == '"' || input[j] == '\'')
	{
		if (in_q && input[j] == in_q)
			in_q = 0;
		else if (!in_q)
			in_q = input[j];
	}
	return (size);
}

int	update_in_q(char *input, int j, int in_q)
{
	if (in_q && input[j] == in_q)
		in_q = 0;
	else if (!in_q)
		in_q = input[j];
	return (in_q);
}

char	*set_tmp(char *input, int j, char *tmp)
{
	if (input[j - 1] != ' ')
	{
		if (!(input[j] == '<' && input[j - 1] == '<') || \
				(input[j] == '>' && input[j - 1] == '>'))
			tmp = ft_strjoin(tmp, " ");
	}
	tmp = ft_strjoin(tmp, ft_substr(input, j, 1));
	if (input[j + 1] != ' ' && input[j + 1] != input[j])
		tmp = ft_strjoin(tmp, " ");
	return (tmp);
}

char	*allocate_and_check_tmp(int size)
{
	char	*tmp;

	tmp = (char *)malloc((size + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}
