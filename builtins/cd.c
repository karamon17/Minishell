/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:24:40 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/22 18:54:02 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_changepwd(t_minishell *shell, char *cmd)
{
	char **envp;
	char buf[PATH_MAX];
	int i;

	i = 0;
	envp = shell->envp;
	getcwd(buf, PATH_MAX);
	while(envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD", 6))
			exit(0);
		i++;
	}
	envp[i] = ft_strjoin("OLDPWD=", buf);
	i = 0;
	while(envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD", 3))
			exit(0);
		i++;
	}
	envp[i] = ft_strjoin("PWD=", cmd);
}

void printenv(t_minishell *shell)
{
	int i = 0;
	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
}

int	ft_cd(t_minishell *shell, t_token *token)
{
	char		*cmd;
	//int			error;

	if (!token->next->data || (token->next->data[0] == '~' && !token->next->data[1]))
		cmd = ft_getenv(shell, "HOME");
	else if((token->next->data[0] == '~' && token->next->data[1]))
		cmd = ft_strjoin(ft_getenv(shell, "HOME"), token->next->data + 1);
	else
		cmd = token->next->data;
	printf("%s\n", cmd);
	if (!access(cmd, F_OK))
	{
		chdir(cmd);
		ft_changepwd(shell, cmd);
		printenv(shell);
	}
	return (0);
}