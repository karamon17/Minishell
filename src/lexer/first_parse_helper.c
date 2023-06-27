/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:00:16 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/27 14:00:18 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_norm_helper(char *tmp, t_token *new, int i)
{
	if (tmp[i] == '\'')
		i = s_quotes(tmp, i + 1, &new);
	else if (tmp[i] == '"')
		i = d_quotes(tmp, i + 1, &new);
	else if (tmp[i] != ' ')
		i = append_word(tmp, i + 1, &new);
	else if (tmp[i] == ' ')
	{
		while (tmp[i + 1] == ' ')
			i++;
	}
	else if (tmp[i] == '<' || tmp[i] == '>')
	{
		if (tmp[i + 1] == tmp[i])
		{
			free(new);
			new = ft_new_token(ft_substr(tmp, i, 2));
			i++;
		}
		else
		{
			free(new);
			new = ft_new_token(ft_substr(tmp, i, 1));
		}
	}
	return (i);
}

void	cut_spaces(t_token **tokens)
{
	t_token	*tmp;

	tmp = (*tokens);
	while (tmp)
	{
		if (tmp->data[0] == ' ')
		{
			tmp = delete_token(tokens, tmp);
		}
		else
			tmp = tmp->next;
	}
}

int	is_special_token(char *token)
{
	return (ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0);
}
