/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:42:34 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/21 17:04:58 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(t_shell *shell, t_constr *constr, int *pid, t_token *head)
{
	*pid = fork();
	if (*pid == -1)
		return (ft_fork_error(constr));
	if (*pid == 0)
	{
		if (constr->command && !constr->prev)
		{
			dup2(constr->fd[1], 1);
			close(constr->fd[1]);
		}
		else if (constr->command)
		{
			dup2(constr->prev->fd[0], 0);
			dup2(constr->fd[1], 1);
			ft_close_pipe(constr->prev->fd);
		}
		else
		{
			dup2(constr->prev->fd[0], 0);
			ft_close_pipe(constr->prev->fd);
		}
		if (!execute_builtin(shell))
			execute(shell, head);
		exit(g_error_status);
	}
}

int	ft_emptypipe(t_constr *constr)
{
	if (constr->command && !ft_strncmp(constr->command, "|", 2)
		&& !constr->next)
	{
		g_error_status = 258;
		ft_putstr_fd("Minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(constr->command, 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	else if (constr->command && !ft_strncmp(constr->command, "|", 2)
		&& !constr->next->data[0])
	{
		g_error_status = 258;
		ft_putstr_fd("Minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(constr->command, 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

int	check_builtin(t_shell *shell)
{
	t_token	*tmp;
	char	*low;
	int		res;

	tmp = shell->tokens;
	low = str_lower(tmp->data);
	res = (ft_strncmp(low, "pwd", 4)
			|| ft_strncmp(tmp->data, "cd", 3)
			|| ft_strncmp(low, "env", 4)
			|| ft_strncmp(tmp->data, "exit", 5)
			|| ft_strncmp(tmp->data, "unset", 6)
			|| ft_strncmp(tmp->data, "export", 7)
			|| ft_strncmp(low, "echo", 5));
	free(low);
	return (res);
}

void	ft_mainpipe(t_shell *shell, t_constr *constr, t_token *head)
{
	char	*path;
	pid_t	pid;

	if ((constr->command && !ft_strncmp(constr->command, "|", 2)) || \
		(constr->prev && constr->prev->command
			&& !ft_strncmp(constr->prev->command, "|", 2)))
	{
		path = check_path(shell);
		if (!path && !check_builtin(shell))
			ft_error_path(shell);
		else
		{
			free(path);
			if (!g_error_status)
			{
				pipe(constr->fd);
				ft_child(shell, constr, &pid, head);
			}
		}
	}
	else if (constr->prev && constr->prev->command && ft_strncmp(constr->prev->command, "|", 2))
			return ;
	else if ((!constr->command && !execute_builtin(shell)) || (constr->command && ft_strncmp(constr->command, "|", 2) && !execute_builtin(shell)))
		execute(shell, head);
}

void	ft_pipex(t_shell *shell)
{
	t_constr	*constr;
	t_token		*head;

	head = shell->tokens;
	constr = shell->constrs;
	while (constr)
	{
		if (ft_emptypipe(constr))
			return ;
		ft_mainpipe(shell, constr, head);
		move_shell_tokens(shell);
		if (constr->prev && !ft_strncmp(constr->prev->command, "|", 2) && !g_error_status)
			ft_close_pipe(constr->prev->fd);
		shell->constrs = constr->next;
		constr = shell->constrs;
	}
	while (wait(NULL) != -1)
		;
}
