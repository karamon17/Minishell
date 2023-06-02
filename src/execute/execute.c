/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:11:11 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/02 18:38:53 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_command(t_shell *shell, char *path)
{
	t_shell *tmp;
	pid_t pid;
	tmp = shell;

	pid = fork();
	if (pid == 0)
	{
		execve(path, ft_split(shell->constrs->data, ' '), NULL);
	}
	else
	{
		wait(NULL);
	}
	return (0);
}

int	execute(t_shell *shell)
{
	char **path;
	char *tmp;
	int i;

	path = ft_split(ft_getenv(shell, "PATH"), ':');
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		tmp = path[i];
		path[i] = ft_strjoin(path[i], shell->tokens->data);
		free(tmp);
		i++;
	}
	i = 0;
	while (path[i])
	{
		if (!access(path[i], X_OK))
			break;
		i++;
	}
	execute_command(shell, path[i]);
	return (0);
}
