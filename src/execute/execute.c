/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:11:11 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/22 11:21:45 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_exec(t_shell *shell)
{
	if (shell->fd != 1)
		dup2(shell->fd, 1);
	if (!shell->constrs->command && shell->constrs->prev
		&& shell->constrs->prev->command && !g_error_status)
	{
		dup2(shell->constrs->prev->fd[0], 0);
		ft_close_pipe(shell->constrs->prev->fd);
	}
}

void	open_stuff(t_shell *shell, char *path, char **argv, char **env2darray)
{
	int			pid;
	t_const		*example;
	//int			fd;
	int			status;

	//fd = 1;
	example = shell->constrs;
	pid = fork();
	signal(SIGINT, sigint_handler2);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
	{
		if (shell->fd == 1)
			shell->fd = open(example->next->data, O_RDONLY, 0644);
		if (shell->fd == -1)
			return (ft_print_error_red(example->next->data));
		dup2(shell->fd, 0);
		ft_child_exec(shell);
		argv = ft_split(shell->constrs->data, ' ');
		env2darray = env_to_2darray(shell);
		execve(path, argv, env2darray);
		ft_exec_error(shell->constrs->data, argv, env2darray);
	}
	if (shell->fd != 1)
		close(shell->fd);
	waitpid(shell->fd, &status, 0);
}

int	exec_comm(t_shell *shell, char *path)
{
	t_helper	hp;

	hp.env2darray = NULL;
	hp.argv = NULL;
	hp.pid = 0;
	if (!g_error_status)
	{
		if (shell->flag != 1)
			return (open_stuff(shell, path, hp.argv, hp.env2darray), 0);
		hp.pid = fork();
		signal(SIGINT, sigint_handler2);
		if (hp.pid == -1)
			return (ft_exec_error(NULL, NULL, NULL));
		if (hp.pid == 0)
		{
			ft_child_exec(shell);
			hp.argv = ft_split(shell->constrs->data, ' ');
			hp.env2darray = env_to_2darray(shell);
			execve(path, hp.argv, hp.env2darray);
			ft_exec_error(shell->constrs->data, hp.argv, hp.env2darray);
		}
	}
	waitpid(hp.pid, &(hp.status), 0);
	return (hp.status / 256);
}

char	*check_path(t_shell *shell)
{
	char	**path;
	char	*res;
	int		i;
	char	*to_free;

	to_free = ft_getenv(shell, "PATH");
	path = ft_split(to_free, ':');
	free(to_free);
	i = -1;
	if (!path)
		return (0);
	while (path[++i])
	{
		path[i] = ft_mystrjoin(path[i], "/");
		path[i] = ft_mystrjoin(path[i], shell->tokens->data);
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
	char		*str_path;
	t_const		*example;

	example = shell->constrs;
	if (ft_strchr(shell->tokens->data, '/')
		&& !access(shell->tokens->data, X_OK))
		str_path = ft_strdup(shell->tokens->data);
	else
		str_path = check_path(shell);
	shell->fd = file_check(example, shell->fd, &shell->flag);
	if (shell->fd == -1)
	{
		free(str_path);
		return (g_error_status);
	}
	if (!str_path)
		g_error_status = ft_exec_error(shell->tokens->data, NULL, NULL);
	else
		g_error_status = exec_comm(shell, str_path);
	close_file(shell->fd);
	free(str_path);
	return (0);
}
