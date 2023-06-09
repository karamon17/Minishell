/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:01:03 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/27 14:01:05 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(char *content)
{
	t_token	*new;

	if (!content)
		return (NULL);
	new = (t_token *) malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->data = ft_strdup(content);
	new->type = 0;
	new->next = NULL;
	free(content);
	return (new);
}

t_token	*ft_token_last(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			return (tmp);
	}
	return (tmp);
}

void	ft_token_add_back(t_token **stack, t_token *new)
{
	t_token	*n;

	if (*stack)
	{
		n = ft_token_last(*stack);
		n->next = new;
		new->next = NULL;
	}
	else
	{
		*stack = new;
		(*stack)->next = NULL;
	}
}

int	ft_token_size(t_token *head)
{
	size_t	i;
	t_token	*tmp;

	tmp = head;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
