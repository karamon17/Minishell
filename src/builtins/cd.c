/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:24:40 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/14 14:55:27 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_oldpwd(t_shell *shell)
{
	t_env	*pointer;

	pointer = shell->env_lst;
	while (pointer)
	{
		if (!ft_strncmp(pointer->key, "OLDPWD", 6))
			break ;
		pointer = pointer->next;
	}
	if (pointer)
		return (1);
	return (0);
}

void	ft_change_oldpwd(t_shell *shell, char *copy)
{
	char	buf[PATH_MAX];
	t_env	*tmp;
	char	*to_free;

	getcwd(buf, PATH_MAX);
	tmp = shell->env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", 6))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		ft_add_env_back(shell->env_lst, "OLDPWD", buf, ENV);
	else
	{
		to_free = tmp->value;
		tmp->value = copy;
		free(to_free);
	}
}

void	ft_changepwd(t_shell *shell)
{
	char	buf[PATH_MAX];
	t_env	*tmp;
	char	*copy;
	char	*to_free;

	getcwd(buf, PATH_MAX);
	tmp = shell->env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
			break ;
		tmp = tmp->next;
	}
	copy = ft_strdup(tmp->value);
	to_free = tmp->value;
	tmp->value = ft_strdup(buf);
	free(to_free);
	ft_change_oldpwd(shell, copy);
}

void	ft_chdir(t_shell *shell, char *cmd)
{
	char	buf[PATH_MAX];
	DIR		*tmp;

	getcwd(buf, PATH_MAX);
	if (!access(cmd, F_OK))
	{
		if (!check_oldpwd(shell))
			ft_add_env_back(shell->env_lst, "OLDPWD", buf, ENV);
		tmp = opendir(cmd);
		if (!tmp)
			ft_cdprint_error(cmd);
		else if (chdir(cmd) == -1)
		{
			g_error_status = 1;
			ft_putstr_fd("Minishell : cd: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		if (tmp)
			closedir(tmp);
		ft_changepwd(shell);
	}
	else
		ft_cdprint_error2(cmd);
}

void	ft_cd(t_shell *shell, int *flag)
{
	char	*cmd;
	t_token	*token;

	token = shell->tokens->next;
	*flag = 1;
	if (!token || (token->data[0] == '~' && !token->data[1]))
		cmd = ft_getenv(shell, "HOME");
	else if ((token->data[0] == '~' && token->data[1]))
		cmd = ft_strjoin(ft_getenv(shell, "HOME"), token->data + 1);
	else if (token->data[0] == '-' && !token->data[1])
	{
		if (!ft_getenv(shell, "OLDPWD"))
		{
			g_error_status = 1;
			ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
			return ;
		}
		cmd = ft_getenv(shell, "OLDPWD");
	}
	else
		cmd = token->data;
	ft_chdir(shell, cmd);
	if (token && token->data[0] == '-' && !token->data[1] && !g_error_status)
		printf("%s\n", ft_getenv(shell, "PWD"));
	return ;
}
