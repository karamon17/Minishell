/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:54:26 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/21 17:11:09 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *isolate_str(char *str)
{
    int i;
    int j;
    i = 0;
    while (str[i] != ' ')
        i++;
    while  (str[i] == ' ')
        i++;
    j = i;
    while (str[i] != ' ' && str[i])
        i++;
    return (ft_substr(str, j, i));
}

static void	fill_file(char *overwrite, char *file)
{
	int	fd;

    overwrite = isolate_str(overwrite);
	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY);
	write(fd, overwrite, ft_strlen(overwrite));
    write(fd, "\n", 1);
	close(fd);
}

static void	append_to_file(char *overwrite, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_APPEND | O_WRONLY);
	write(fd, overwrite, ft_strlen(overwrite));
    write(fd, "\n", 1);
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
		ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n",
			2);
		exit(1);
	}	
	if (!ft_strncmp(tmp->command, ">", 2) || !ft_strncmp(tmp->command, ">>", 3))
	{
		if (tmp)
			overwrite = tmp->data;
		else
			overwrite = "";
		file = tmp->next->data;
	}
	if (!ft_strncmp(tmp->command, ">", 2))
		fill_file(overwrite, file);
	else if (!ft_strncmp(tmp->command, ">>", 3))
		append_to_file(overwrite, file);
}
