/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:38:27 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/20 14:30:34 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*cut_command_quotes(t_token *tokens)
{
	int		i;
	char	*cpy;
	char	*tmp_str;
	t_token	*tmp;
	char	*to_free;

	tmp = tokens;
	while (tmp != NULL)
	{
		i = -1;
		cpy = ft_calloc(1, sizeof(char));
		while (tmp->data[++i])
		{
			if (tmp->data[i] == '\'')
				continue ;
			if (tmp->data[i] == '"')
				continue ;
			tmp_str = cpy;
			to_free = ft_substr(tmp->data, i, 1);
			cpy = ft_strjoin(cpy, to_free);
			free(tmp_str);
			free(to_free);
		}
		to_free = tmp->data;
		tmp->data = ft_strdup(cpy);
		free(to_free);
		tmp = tmp->next;
		free(cpy);
	}
	return (tokens);
}

t_token *delete_token(t_token **head, t_token *to_delete)
{
	t_token	*prev_node;

	if (*head == NULL || to_delete == NULL)
		return (NULL);
	if (*head == to_delete)
	{
		(*head)->next = to_delete->next;
		free(to_delete->data);
		free(to_delete);
		return (NULL);
	}
	prev_node = *head;
	while (prev_node->next != NULL && prev_node->next != to_delete)
		prev_node = prev_node->next;
	if (prev_node->next == NULL)
		return (NULL);
	prev_node->next = to_delete->next;
	free(to_delete->data);
	free(to_delete);
	return (prev_node->next);
}

t_token	*check_options(t_token *tokens)
{
	t_token	*tmp;
	t_token	*to_delete;
	char	*temp_str;
	char	*to_free;

	tmp = tokens->next;
	to_free = NULL;
	if (tmp)
		to_free = ft_strtrim(tmp->data, "n");
	if (tmp && tmp->data[0] == '-'
		&& !ft_strncmp(to_free, "-", 2))
	{
		temp_str = tmp->data;
		tmp->data = ft_strdup("-n");
		free(temp_str);
		tmp = tmp->next;
		free(to_free);
	}
	else
	{
		free(to_free);
		return (tokens);
	}
	to_free = ft_strtrim(tmp->data, "n");
	while (tmp && tmp->data[0] == '-'
		&& !ft_strncmp(to_free, "-", 2))
	{
		to_delete = tmp;
		tmp = tmp->next;
		delete_token(&tokens, to_delete);
		free(to_free);
	}
	free(to_free);
	return (tokens);
}

t_token	*stugel(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp)
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
