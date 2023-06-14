/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:54:26 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 17:27:48 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_file(char *overwrite, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY);
	write(fd, overwrite, ft_strlen(overwrite));
	close(fd);
}

static void	append_to_file(char *overwrite, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_APPEND | O_WRONLY);
	write(fd, overwrite, ft_strlen(overwrite));
	close(fd);
}

void	redirect_output(t_constr *cmds)
{
	t_constr	*tmp;
	char		*overwrite;
	char		*file;

	tmp = cmds;
	if (!tmp->next->data)
	{
		printf("syntax error near unexpected token `newline'");
		exit(1);
	}	
	if (!ft_strncmp(tmp->data, ">", 2) || !ft_strncmp(tmp->data, ">>", 3))
	{
		if (tmp->prev)
			overwrite = tmp->prev->data;
		else
			overwrite = "";
		file = tmp->next->data;
	}
	if (!ft_strncmp(tmp->data, ">", 2))
		fill_file(overwrite, file);
	else if (!ft_strncmp(tmp->data, ">>", 3))
		append_to_file(overwrite, file);
}
