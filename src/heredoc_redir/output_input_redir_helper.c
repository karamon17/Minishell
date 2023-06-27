/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_input_redir_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:59:53 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/27 13:59:54 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int file_check(t_constr *example, int fd, int *flag)
{
	t_constr	*tmp;

	tmp = example;
	if (tmp->command && !ft_strncmp(tmp->command, ">", 2))
		fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (tmp->command && !ft_strncmp(tmp->command, ">>", 3))
		fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (tmp->command && !ft_strncmp(tmp->command, "<", 2))
	{
		fd = open(tmp->next->data, O_CREAT | O_RDONLY | O_TRUNC, 0644);
		*flag = 2;
		return (fd);
	}
	if (tmp->next && tmp->next->command)
	{
		tmp = tmp->next;
		while (tmp && (tmp->command && (!ft_strncmp(tmp->command, ">", 2) || !ft_strncmp(tmp->command, ">>", 3))))
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
	*flag = 1;
	return (fd);
}
