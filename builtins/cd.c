/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:24:40 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/23 15:06:53 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_changepwd(t_shell *shell)
{
	char buf[PATH_MAX];
	t_env *tmp;

	tmp = shell->env_lst;
	getcwd(buf, PATH_MAX);
	while(tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", 6))
			break;
		tmp = tmp->next;
	}
	tmp->value = ft_strdup(buf);
	tmp = shell->env_lst;
	while(tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
			break;
		tmp = tmp->next;
	}
	tmp->value = ft_strdup(buf);
}

void printenv(t_shell *shell)
{
	while (shell->env_lst)
	{
		printf("%s\n", shell->env_lst->key);
		printf("%s\n", shell->env_lst->value);
		shell->env_lst = shell->env_lst->next;
	}
}

int	ft_cd(t_shell *shell)
{
	char		*cmd;
	//int			error;

	printf("%s\n", shell->tokens->data);
	printf("%s\n", shell->tokens->next->data);
	if (!shell->tokens->next->data || (shell->tokens->next->data[0] == '~' && !shell->tokens->next->data[1]))
		cmd = ft_getenv(shell, "HOME");
	else if((shell->tokens->next->data[0] == '~' && shell->tokens->next->data[1]))
		cmd = ft_strjoin(ft_getenv(shell, "HOME"), shell->tokens->next->data + 1);
	else
		cmd = shell->tokens->next->data;
	//printf("%s\n", cmd);
	if (!access(cmd, F_OK))
	{
		chdir(cmd);
		ft_changepwd(shell);
		printenv(shell);
	}
	return (0);
}