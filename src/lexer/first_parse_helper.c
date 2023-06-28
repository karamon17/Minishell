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
			new = ft_new_token(ft_substr(tmp, i++, 2));
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

char	message_status(void)
{
	g_error_status = 258;
	ft_putstr_fd("Minishell : syntax error: unexpected end of file\n", 2);
	return ('E');
}

t_token	*check_redirects(t_token *new)
{
	t_token	*tmp;

	tmp = new;
	if (ft_token_size(tmp) == 1 && (!ft_strncmp(tmp->data, "<", 2) || \
	!ft_strncmp(tmp->data, ">", 2) || !ft_strncmp(tmp->data, ">>", 3)))
		tmp->type = message_status();
	while (tmp)
	{
		if (tmp->next && (!ft_strncmp(tmp->data, "<", 2) \
		|| !ft_strncmp(tmp->data, ">", 2) \
		|| !ft_strncmp(tmp->data, ">>", 3) \
		|| !ft_strncmp(tmp->data, "<<", 3)) \
		&& (!ft_strncmp(tmp->next->data, "<", 2) \
		|| !ft_strncmp(tmp->next->data, ">", 2) \
		|| !ft_strncmp(tmp->next->data, ">>", 3) \
		|| !ft_strncmp(tmp->next->data, "<<", 3)))
		{
			tmp->type = message_status();
			break ;
		}
		tmp = tmp->next;
	}
	return (new);
}
