/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins-execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:24:02 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/02 18:47:29 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *str_lower(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int	execute_builtin(t_shell *shell)
{
	t_token *tmp;
	int *flag;

	flag = malloc(sizeof(int));
	*flag = 0;
	tmp = shell->tokens;
	if (!ft_strncmp(str_lower(tmp->data), "pwd", 3))
		ft_pwd(flag);
	else if (!ft_strncmp(tmp->data, "cd", 3))
		ft_cd(shell, flag);
	else if (!ft_strncmp(str_lower(tmp->data), "env", 3))
		ft_env(shell, flag);
	else if (!ft_strncmp(tmp->data, "exit", 4))
		ft_exit(shell, flag);
	else if (!ft_strncmp(tmp->data, "unset", 5))
		ft_unset(shell, flag);
	else if (!ft_strncmp(tmp->data, "export", 6))
		ft_export(shell, flag);
	else if (!ft_strncmp(str_lower(tmp->data), "echo", 4))
		ft_echo(shell, flag);
	return (*flag);
}