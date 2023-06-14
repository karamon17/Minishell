/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:38:27 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 18:01:36 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*cut_command_quotes(t_token *tokens)
{
	int		i;
	char	*cpy;
	t_token	*tmp;
	char	c;

	tmp = tokens;
	while (tmp != NULL)
	{
		c = tmp->data[0];
		i = -1;
		cpy = ft_calloc(1, sizeof(char));
		while (tmp->data[++i])
		{
			if (tmp->data[i] == '\'')
				continue ;
			if (tmp->data[i] == '"')
				continue ;
			cpy = ft_strjoin(cpy, ft_substr(tmp->data, i, 1));
		}
		tmp->data = cpy;
		tmp = tmp->next;
	}
	return (tokens);
}

void	delete_token(t_token **head, t_token *to_delete)
{
	t_token	*prev_node;

	if (*head == NULL || to_delete == NULL)
		return ;
	if (*head == to_delete)
	{
		(*head)->next = to_delete->next;
		free(to_delete);
		return ;
	}
	prev_node = *head;
	while (prev_node->next != NULL && prev_node->next != to_delete)
		prev_node = prev_node->next;
	if (prev_node->next == NULL)
		return ;
	prev_node->next = to_delete->next;
	free(to_delete);
}

t_token	*check_options(t_token *tokens)
{
	t_token	*tmp;
	t_token	*to_delete;
	int		found;

	tmp = tokens;
	found = 0;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->data, "-n") == 0)
			found = 1;
		else if (found)
		{
			if (tmp->data[0] == '-' && ft_strlen(tmp->data) > \
					1 && strspn(tmp->data, "-"))
			{
				to_delete = tmp;
				tmp = tmp->next;
				delete_token(&tokens, to_delete);
				continue ;
			}
		}
		tmp = tmp->next;
	}
	return (tokens);
}

t_token	*stugel(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->data, "echo", 5) == 0 && i == 0)
			tokens = check_options(tmp);
		tmp = tmp->next;
		i++;
	}
	tmp = tokens;
	tokens = cut_command_quotes(tmp);
	return (tokens);
}
