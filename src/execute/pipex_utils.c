/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:57:48 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/12 17:07:13 by gkhaishb         ###   ########.fr       */
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
