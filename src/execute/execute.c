/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:11:11 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/16 13:42:50 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_error(char *str)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int	execute_command(t_shell *shell, char *path)
{
	pid_t	pid;

	if (!path)
	{
		ft_exec_error(shell->tokens->data);
		return (127);
	}
	if (!g_error_status)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Minishell: fork: Resource temporarily unavailable\n", 2);
			g_error_status = 1;
			return (1);
		}
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
	}
	return (1);
}

void	ft_free_path(char **path)
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
	char	*res;
	char	*tmp;
	int		i;

	path = ft_split(ft_getenv(shell, "PATH"), ':');
	i = -1;
	while (path[++i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		tmp = path[i];
		path[i] = ft_strjoin(path[i], shell->tokens->data);
		free(tmp);
	}
	i = -1;
	while (path[++i])
	{
		if (!access(path[i], X_OK))
			break ;
	}
	res = ft_strdup(path[i]);
	ft_free_path(path);
	return (res);
}

int	execute(t_shell *shell)
{
	char	*str_path;

	if (!access(shell->tokens->data, X_OK))
		str_path = ft_strdup(shell->tokens->data);
	else
		str_path = check_path(shell);
	g_error_status = execute_command(shell, str_path);
	free(str_path);
	return (0);
}
