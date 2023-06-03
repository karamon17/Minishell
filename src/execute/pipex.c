/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:42:34 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/03 18:07:33 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void move_shell_tokens(t_shell *shell)
{
	char *token;
	token = shell->tokens->data;
	while (shell->tokens->next && token[0] != '|' && token[0] != '<' && token[0] != '>' && ft_strncmp(token, "<<", 2) != 0 && ft_strncmp(token, ">>", 2) != 0)
	{
		shell->tokens = shell->tokens->next;
		token = shell->tokens->data;
	}
	shell->tokens = shell->tokens->next;
}

void ft_child(t_shell *shell, t_constr *constr)
{
	char *construction;

	construction = constr->data;
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

void ft_pipex(t_shell *shell)
{
	int	pid;
	t_constr *constr = shell->constrs;
	if (!constr)
		return ;
	while (constr)
	{
		if (constr->command)
			pipe(constr->fd);
		pid = fork();
		if (pid == 0)
		{
			if (constr->next == NULL && constr->prev == NULL)
			{	
				if (!execute_builtin(shell))
					execute(shell);
				exit(0);
			}
			else
				ft_child(shell, constr);
		}
		move_shell_tokens(shell);
		if (constr->prev && constr->prev->command)
			ft_close_pipe(constr->prev->fd);
		constr = constr->next;
	}
	while (wait(NULL) != -1)
		;
}