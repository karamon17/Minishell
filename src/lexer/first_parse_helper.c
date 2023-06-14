/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:03:10 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 18:22:51 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_shell(t_shell **shell)
{
	free_shell(*shell);
}

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
			new = ft_new_token(ft_substr(tmp, i, 2));
			i++;
		}
		else
			new = ft_new_token(ft_substr(tmp, i, 1));
	}
	return (i);
}

void	cut_spaces(t_token **tokens)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = (*tokens);
	tmp2 = tmp;
	while (tmp)
	{
		if (tmp->data[0] == ' ')
			delete_token(tokens, tmp);
		tmp = tmp->next;
	}
}

int	is_special_token(char *token)
{
	return (ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0);
}
