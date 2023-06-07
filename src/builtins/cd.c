/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:24:40 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/07 18:29:50 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_changepwd(t_shell *shell)
{
	char buf[PATH_MAX];
	t_env *tmp;
	char *copy;
	char *to_free;

	getcwd(buf, PATH_MAX);
	tmp = shell->env_lst;
	while(tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
			break;
		tmp = tmp->next;
	}
	copy = ft_strdup(tmp->value);
	to_free = tmp->value;
	tmp->value = ft_strdup(buf);
	free(to_free);
	tmp = shell->env_lst;
	while(tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", 6))
			break;
		tmp = tmp->next;
	}
	to_free = tmp->value;
	tmp->value = copy;
	free(to_free);
}

int	ft_cd(t_shell *shell, int *flag)
{
	char	*cmd;
	
	*flag = 1;
	if (!shell->tokens->next || (shell->tokens->next->data[0] == '~' && !shell->tokens->next->data[1]))
		cmd = ft_getenv(shell, "HOME");
	else if((shell->tokens->next->data[0] == '~' && shell->tokens->next->data[1]))
		cmd = ft_strjoin(ft_getenv(shell, "HOME"), shell->tokens->next->data + 1);
	else if (shell->tokens->next->data[0] == '-' && !shell->tokens->next->data[1])
	{
		if (!ft_getenv(shell, "OLDPWD"))
			return (0);
		cmd = ft_getenv(shell, "OLDPWD");
	}
	else
		cmd = shell->tokens->next->data;
	if (shell->tokens->next && shell->tokens->next->data[0] == '-' && !shell->tokens->next->data[1])
		printf("%s\n", ft_getenv(shell, "OLDPWD"));
	if (!access(cmd, F_OK))
	{
		chdir(cmd);
		ft_changepwd(shell);
	}
	return (0);
}