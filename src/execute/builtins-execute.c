/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins-execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:24:02 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/16 19:37:18 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_lower(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup(str);
	while (res[i])
	{
		res[i] = ft_tolower(res[i]);
		i++;
	}
	return (res);
}

int	execute_builtin(t_shell *shell)
{
	t_token	*tmp;
	int		flag[1];
	char	*low;

	*flag = 0;
	tmp = shell->tokens;
	low = str_lower(tmp->data);
	if (!ft_strncmp(low, "pwd", 4))
		ft_pwd(flag);
	else if (!ft_strncmp(tmp->data, "cd", 3))
		ft_cd(shell, flag);
	else if (!ft_strncmp(low, "env", 4))
		ft_env(shell, flag);
	else if (!ft_strncmp(tmp->data, "exit", 5))
		ft_exit(shell, flag);
	else if (!ft_strncmp(tmp->data, "unset", 6))
		ft_unset(shell, flag);
	else if (!ft_strncmp(tmp->data, "export", 7))
		ft_export(shell, flag);
	else if (!ft_strncmp(low, "echo", 5))
		ft_echo(shell, flag);
	free(low);
	// else if (!ft_strncmp(tmp->data, ">", 2) || !ft_strncmp(tmp->data, ">>", 3))
	// 		redirect_output(shell->constrs);
	return (*flag);
}
