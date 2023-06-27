/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:58:14 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/27 16:44:58 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delnode(t_shell *shell, t_env *env)
{
	t_env	*tmp;

	tmp = shell->env_lst;
	while (tmp->next != env)
		tmp = tmp->next;
	tmp->next = env->next;
	free(env->key);
	free(env->value);
	free(env);
}

int	ft_checkletter_unset(char *arg)
{
	int	res;

	if (!arg[0])
		return (0);
	res = ((arg[0] >= 'a' && arg[0] <= 'z') || \
		(arg[0] >= 'A' && arg[0] <= 'Z') || arg[0] == '_');
	res = !ft_strchr(arg, '-') && !ft_strchr(arg, '{')
		&& !ft_strchr(arg, '}') && !ft_strchr(arg, '$')
		&& !ft_strchr(arg, '#') && !ft_strchr(arg, '*')
		&& !ft_strchr(arg, '.') && !ft_strchr(arg, '/')
		&& !ft_strchr(arg, '@') && !ft_strchr(arg, '=')
		&& !ft_strchr(arg, '^');
	if (ft_strchr(arg, '+') && ft_strchr(arg, '+') != &arg[ft_strlen(arg) - 1])
		res = 0;
	return (res);
}

void	ft_printerror_unset(char *tmp)
{
	g_error_status = 1;
	ft_putstr_fd("Minishell: unset: ", 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

void	ft_unset(t_shell *shell, int *flag)
{
	t_token	*tmp;
	t_env	*env;

	*flag = 1;
	tmp = shell->tokens->next;
	if (!tmp)
		return ;
	while (tmp && tmp->data[0] != '|' && tmp->data[0] != '<'
		&& tmp->data[0] != '>' && ft_strncmp(tmp->data, "<<", 2) != 0
		&& ft_strncmp(tmp->data, ">>", 2) != 0)
	{
		env = shell->env_lst;
		if (!ft_checkletter_unset(tmp->data))
			ft_printerror_unset(tmp->data);
		else
		{
			while (env)
			{
				if (!ft_strncmp(tmp->data, env->key, ft_strlen(env->key)))
					delnode(shell, env);
				env = env->next;
			}
		}
		tmp = tmp->next;
	}
}
