/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:31:45 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/07 19:02:17 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int ft_export(t_shell *shell, int *flag)
{
	t_env *env;
	char *value;
	char **tmp;
	int i;
	
	*flag = 1;
	tmp = ft_split(shell->constrs->data, ' ');
	i = 1;
	while(tmp[i])
	{
		if (!ft_strchr(tmp[i], '='))
			return (0);
		else
		{
			value = ft_strchr(tmp[i], '=') + 1;
			*(ft_strchr(tmp[i], '=')) = 0;
		}
		env = check_key_env(shell->env_lst, tmp[i]);
		if (!env)
			ft_add_env_back(shell->env_lst, tmp[i], value, ENV);
		else
		{
			free(env->value);
			env->value = ft_strdup(value);
		}
		i++;
	}
	return (0);
}