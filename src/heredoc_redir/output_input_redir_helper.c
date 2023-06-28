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

int	open_helper(int *flag, t_const *tmp)
{
	int	fd;

	fd = open(tmp->next->data, O_RDONLY, 644);
	if (fd == -1)
		ft_print_error_red(tmp->next->data);
	*flag = 2;
	return (fd);
}

int	file_check(t_const *example, int fd, int *flag)
{
	t_const	*tmp;

	tmp = example;
	if (tmp->command && !ft_strncmp(tmp->command, ">", 2))
		fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (tmp->command && !ft_strncmp(tmp->command, ">>", 3))
		fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (tmp->command && !ft_strncmp(tmp->command, "<", 2))
		return (open_helper(flag, tmp));
	if (tmp->next && tmp->next->command)
	{
		tmp = tmp->next;
		while (tmp && (tmp->command && (!ft_strncmp(tmp->command, ">", 2) \
		|| !ft_strncmp(tmp->command, ">>", 3))))
		{
			close_file(fd);
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
