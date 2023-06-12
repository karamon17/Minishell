/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:42:34 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/12 17:14:54 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(t_shell *shell, t_constr *constr)
{
	pipe(constr->fd);
	if (fork() == 0)
	{
		if (constr->command && shell->constrs == constr)
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
			execute(shell);
		exit(0);
	}
}

int	ft_emptypipe(t_constr *constr)
{
	if (constr->command && !ft_strncmp(constr->command, "|", 2)
		&& !constr->next)
	{
		g_error_status = 258;
		printf("Minishell: syntax error near unexpected token '%s'\n",
			constr->command);
		return (1);
	}
	return (0);
}

void	ft_mainpipe(t_shell *shell, t_constr *constr)
{
	if (constr->command && !ft_strncmp(constr->command, "|", 2))
	{
		if (!check_path(shell))
		{
			g_error_status = 127;
			printf("Minishell: %s: command not found\n",
				shell->tokens->data);
		}
		ft_child(shell, constr);
	}
	else if (!constr->command && !execute_builtin(shell))
		execute(shell);
}

void	ft_pipex(t_shell *shell)
{
	t_constr	*constr;

	constr = shell->constrs;
	while (constr)
	{
		if (ft_emptypipe(constr))
			return ;
		ft_mainpipe(shell, constr);
		move_shell_tokens(shell);
		if (constr->prev && constr->prev->command)
			ft_close_pipe(constr->prev->fd);
		shell->constrs = constr->next;
		constr = shell->constrs;
	}
	while (wait(NULL) != -1)
		;
}
