/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins-execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:24:02 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/27 14:31:36 by gkhaishb         ###   ########.fr       */
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

int	builtin_conditonals(t_shell *shell, t_token *tmp, t_constr *example)
{
	int		flag[1];
	char	*low;

	*flag = 0;
	low = str_lower(tmp->data);
	if (!ft_strncmp(low, "pwd", 4))
		ft_pwd(flag, example);
	else if (!ft_strncmp(tmp->data, "cd", 3))
		ft_cd(shell, example);
	else if (!ft_strncmp(low, "env", 4))
		ft_env(shell, flag, example);
	else if (!ft_strncmp(tmp->data, "exit", 5))
		ft_exit(shell, flag, example);
	else if (!ft_strncmp(tmp->data, "unset", 6))
		ft_unset(shell, flag, example);
	else if (!ft_strncmp(tmp->data, "export", 7))
		ft_export(shell, flag, example);
	else if (!ft_strncmp(low, "echo", 5))
		ft_echo(shell, flag, example);
	free(low);
	return (*flag);
}

int	execute_builtin(t_shell *shell)
{
	t_token	*tmp;
	int		flag[1];
	t_constr	*example;
	int			fd;

	fd = 1;
	example = shell->constrs;
	*flag = 0;
	tmp = shell->tokens;
	file_check(example, shell->fd, &shell->flag);
	*flag = builtin_conditonals(shell, tmp, example);
	return (*flag);
}
