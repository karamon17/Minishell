/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:24:02 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/23 19:24:58 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(t_shell *shell)
{
	t_token *tmp;

	tmp = shell->tokens;
	if (!ft_strncmp(tmp->data, "PWD", 3) || !ft_strncmp(tmp->data, "pwd", 3))
		ft_pwd();
	ft_cd(shell);
	return (0);
}