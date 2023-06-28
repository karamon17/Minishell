/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:57:48 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/21 14:48:13 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	move_shell_tokens(t_shell *shell)
{
	char	*token;

	token = shell->tokens->data;
	while (shell->tokens->next && token[0] != '|' && token[0] != '<'
		&& token[0] != '>' && ft_strncmp(token, "<<", 2) != 0
		&& ft_strncmp(token, ">>", 2) != 0)
	{
		shell->tokens = shell->tokens->next;
		token = shell->tokens->data;
	}
	shell->tokens = shell->tokens->next;
}

void	ft_fork_error(t_const *constr)
{
	ft_putstr_fd("Minishell: fork: Resource temporarily unavailable\n", 2);
	g_error_status = 1;
	ft_close_pipe(constr->prev->fd);
}

void	ft_error_path(t_shell *shell)
{
	g_error_status = 127;
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(shell->tokens->data, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	pipex_helper(t_shell *shell)
{
	if (check_builtin(shell))
		execute_builtin(shell);
	else
		execute(shell);
}
