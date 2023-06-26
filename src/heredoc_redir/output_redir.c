/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:54:26 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/22 13:56:31 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int file_check(t_constr *example, int fd)
{
	t_constr	*tmp;

	tmp = example;
	if (tmp->command && !ft_strncmp(tmp->command, ">", 2))
		fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (tmp->command && !ft_strncmp(tmp->command, ">>", 3))
		fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (tmp->next->command)
	{
		tmp = tmp->next;
		while (tmp && (!ft_strncmp(tmp->next->command, ">", 2) || !ft_strncmp(tmp->next->command, ">>", 3)))
		{
			if (fd != 1)
				close(fd);
			if (tmp->command && !ft_strncmp(tmp->command, ">", 2))
				fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (tmp->command && !ft_strncmp(tmp->command, ">>", 3))
				fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
			tmp = tmp->next;
		}
	}
	return (fd);
}
