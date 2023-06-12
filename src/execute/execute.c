/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:11:11 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/12 13:08:16 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_shell *shell, char *path)
{
	pid_t	pid;

	if (!path)
	{
		printf("Minishell: %s: command not found\n", shell->tokens->data);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		if (!shell->constrs->command && shell->constrs->prev
			&& shell->constrs->prev->command)
		{
			dup2(shell->constrs->prev->fd[0], 0);
			ft_close_pipe(shell->constrs->prev->fd);
		}
		exit(execve(path, ft_split(shell->constrs->data, ' '),
				env_to_2darray(shell)));
	}
	else
	{
		wait(NULL);
	}
	return (0);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

char	*check_path(t_shell *shell)
{
	char	**path;
	char	*tmp;
	int		i;

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
			break ;
		i++;
	}
	return (path[i]);
}

int	execute(t_shell *shell)
{
	char	*str_path;

	str_path = check_path(shell);
	error_status = execute_command(shell, str_path);
	//free_path(tmp);
	return (0);
}
