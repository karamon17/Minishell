/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_norm_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:18:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/28 09:18:31 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_norm_helper(t_shell **shell, t_token **tmp)
{
	if (check_next_node(*tmp) == -1)
	{
		(*tmp)->type = print_and_set_type((*tmp)->type);
		return (-1);
	}
	if (exec_heredoc(shell, (*tmp)) == -1)
	{
		(*tmp)->type = print_and_set_type((*tmp)->type);
		return (-1);
	}
	return (1);
}

char	print_and_set_type(char type)
{
	ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
	type = 'E';
	return (type);
}
