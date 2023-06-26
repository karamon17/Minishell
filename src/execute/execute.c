/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:11:11 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/20 17:50:22 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_error(char *str, char **argv, char **env2darray)
{
	if (!argv && !env2darray)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	else if (!str && !argv && !env2darray)
	{
		ft_putstr_fd("Minishell: fork: Resource temporarily unavailable\n", 2);
		g_error_status = 1;
		return (1);
	}
	else
	{
		ft_free_path(argv);
		ft_free_path(env2darray);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
}

void	ft_child_exec(t_shell *shell)
{
	if (!shell->constrs->command && shell->constrs->prev
		&& shell->constrs->prev->command)
	{
		dup2(shell->constrs->prev->fd[0], 0);
		ft_close_pipe(shell->constrs->prev->fd);
	}
}

int	execute_command(t_shell *shell, char *path, t_token *head, t_constr *example)
{
	pid_t	pid;
	char	**argv;
	char	**env2darray;
	int		status;
	char	*check;

	check = prev_node(head, shell->tokens);
	if (!path)
		return (ft_exec_error(shell->tokens->data, NULL, NULL));
	pid = 0;
	if (example->command && !ft_strncmp(example->command, ">", 3))
		shell->fd = open(example->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (example->command && !ft_strncmp(example->command, ">>", 3))
		shell->fd = open(example->next->data, O_CREAT | O_WRONLY, 0644);
	if (!g_error_status)
	{
		pid = fork();
		if (pid == -1)
			return (ft_exec_error(NULL, NULL, NULL));
		if (pid == 0)
		{
			dup2(shell->fd, 1);
			ft_child_exec(shell);
			argv = ft_split(shell->constrs->data, ' ');
			env2darray = env_to_2darray(shell);
			execve(path, argv, env2darray);
			ft_exec_error(shell->constrs->data, argv, env2darray);
		}
	}
	close(shell->fd);
	waitpid(pid, &status, 0);
	return (status / 256);
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

int	execute(t_shell *shell, t_token *head)
{
	char		*str_path;
	t_constr	*example;

	example = shell->constrs;
	if (ft_strchr(shell->tokens->data, '/')
		&& !access(shell->tokens->data, X_OK))
		str_path = ft_strdup(shell->tokens->data);
	else
		str_path = check_path(shell);
	g_error_status = execute_command(shell, str_path, head, example);
	free(str_path);
	return (0);
}
