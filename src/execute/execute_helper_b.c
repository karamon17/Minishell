/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:37:54 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/28 09:37:55 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prev_node(t_token *head, t_token *token)
{
	t_token	*tmp;

	tmp = head;
	if (tmp == token)
		return (NULL);
	while (tmp)
	{
		if (tmp->next == token)
			return (tmp->data);
		tmp = tmp->next;
	}
	return (NULL);
}
