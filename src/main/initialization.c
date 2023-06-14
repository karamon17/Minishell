/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:13:59 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 16:45:21 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*initialize_tokens(t_token *tokens)
{
	tokens = malloc(sizeof(t_token));
	if (!tokens)
		ft_error_exit("Malloc Error: Token Struct");
	tokens->next = NULL;
	tokens->data = NULL;
	return (tokens);
}

t_constr	*initialize_constr(t_constr *constrs)
{
	constrs = malloc(sizeof(t_token));
	if (!constrs)
		ft_error_exit("Malloc Error: Constrs Struct");
	constrs->next = NULL;
	constrs->prev = NULL;
	constrs->data = NULL;
	constrs->command = NULL;
	return (constrs);
}

void	init_shell(t_shell **shell)
{
	(*shell) = malloc(sizeof(t_shell));
	if (!(*shell))
		(*shell)->err_stat = -1;
	else
	{
		(*shell)->err_stat = 0;
		(*shell)->tokens = initialize_tokens((*shell)->tokens);
		(*shell)->constrs = initialize_constr((*shell)->constrs);
		(*shell)->env_lst = NULL;
	}
}
