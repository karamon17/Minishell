/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:39:04 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/12 15:27:28 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell, int *flag, t_constr *example)
{
	t_env	*current;

	shell->fd = 1;
	*flag = 1;
	current = shell->env_lst;
	if (example->command && !ft_strncmp(example->command, ">", 3))
		shell->fd = open(example->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (example->command && !ft_strncmp(example->command, ">", 3))
		shell->fd = open(example->next->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd(current->key, shell->fd);
			ft_putstr_fd("=", shell->fd);
			ft_putstr_fd(current->value, shell->fd);
			ft_putstr_fd("\n", shell->fd);
		}
			current = current->next;
	}
	if (shell->fd != 1)
		close(shell->fd);
}
