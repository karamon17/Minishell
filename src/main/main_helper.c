/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:54:53 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/28 14:54:54 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredocs(t_shell **shell)
{
	if ((*shell)->heredoc_name)
	{
		unlink((*shell)->heredoc_name);
		free((*shell)->heredoc_name);
		(*shell)->heredoc_name = NULL;
	}
}
