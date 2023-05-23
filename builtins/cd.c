/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:24:40 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/23 17:10:29 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_changepwd(t_shell *shell)
{
	char buf[PATH_MAX];
	t_env *tmp;
	char *copy;

	getcwd(buf, PATH_MAX);
	tmp = shell->env_lst;
	while(tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
			break;
		tmp = tmp->next;
	}
	copy = ft_strdup(tmp->value);
	tmp->value = ft_strdup(buf);
	tmp = shell->env_lst;
	while(tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", 6))
			break;
		tmp = tmp->next;
	}
	tmp->value = copy;
}

// void printenv(t_shell *shell)
// {
// 	t_env *current;

// 	current = shell->env_lst;
// 	while (current)
// 	{
// 		printf("%s=", current->key);
// 		printf("%s\n", current->value);
// 		current = current->next;
// 	}
// }

int	ft_cd(t_shell *shell)
{
	char		*cmd;
	//int			error;
	
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
		//printenv(shell);
	}
	return (0);
}