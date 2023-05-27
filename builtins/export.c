/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:31:45 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/27 14:21:52 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *check_key_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)))
			return (env);
		env = env->next;
	}
	return (0);
}

int ft_export(t_shell *shell)
{
	t_token *tmp;
	t_env *env;
	t_env *env_tmp;
	char *value;

	tmp = shell->tokens->next;
	if (!ft_strchr(tmp->data, '='))
		return (0);
	else
	{
		value = ft_strchr(tmp->data, '=') + 1;
		*(ft_strchr(tmp->data, '=')) = 0;
	}
	env = shell->env_lst;
	env_tmp = check_key_env(env, tmp->data);
	if (env_tmp)
	{
		free(env_tmp->value);
		env_tmp->value = ft_strdup(value);
		return (0);
	}
	ft_add_env_back(env, tmp->data, value, ENV);
	return (0);
}