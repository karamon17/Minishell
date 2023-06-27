/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:55:15 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/14 14:10:47 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_withoutn(t_token	*tokens, t_constr *example, int *flag)
{
	int	fd;

	fd = 1;
	fd = file_check(example, fd, flag);
	while (tokens && tokens->data[0] != '|' && tokens->data[0] != '<'
		&& tokens->data[0] != '>' && ft_strncmp(tokens->data, "<<", 2)
		!= 0 && ft_strncmp(tokens->data, ">>", 2) != 0)
	{
		ft_putstr_fd(tokens->data, fd);
		if (tokens->next && tokens->next->data[0] != '|')
			ft_putstr_fd(" ", fd);
		tokens = tokens->next;
	}
	ft_putstr_fd("\n", fd);
	if (fd != 1)
		close(fd);
}

void	ft_echo(t_shell *shell, int *flag, t_constr *example)
{
	t_token	*tokens;

	*flag = 1;
	tokens = shell->tokens->next;

	shell->fd = 1;
	if (!tokens)
	{	
		printf("\n");
		return ;
	}
	if (!ft_strncmp(tokens->data, "-n", 3))
	{	
		tokens = tokens->next;
		shell->fd = file_check(example, shell->fd, &shell->flag);
		while (tokens)
		{
			ft_putstr_fd(tokens->data, shell->fd);
			if (tokens->next && tokens->next->data[0] != '|')
				ft_putstr_fd("\n", shell->fd);
			tokens = tokens->next;
		}
		if (shell->fd != 1)
			close (shell->fd);
	}
	else
		ft_withoutn(tokens, example, &shell->flag);
	if (example->command && !ft_strncmp(example->command, "<", 2))
		printf("\n");
}
