/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:31:45 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/27 16:10:14 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *check_key_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (env);
		env = env->next;
	}
	return (0);
}

int ft_export(t_shell *shell)
{
	t_token *tmp;
	t_env *env;
	char *value;

	tmp = shell->tokens->next;
	if (!ft_strchr(tmp->data, '='))
		return (0);
	else
	{
		value = ft_strchr(tmp->data, '=') + 1;
		*(ft_strchr(tmp->data, '=')) = 0;
	}
	env = check_key_env(shell->env_lst, tmp->data);
	if (!env)
		ft_add_env_back(shell->env_lst, tmp->data, value, ENV);
	else
	{
		free(env->value);
		env->value = ft_strdup(value);
	}
	return (0);
}