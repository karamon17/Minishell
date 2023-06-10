/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:31:45 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/10 18:54:50 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_add(t_shell *shell, t_env *env, char *key, char *value)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			break ;
		env = env->next;
	}
	if (!env)
		ft_add_env_back(shell->env_lst, key, value, ENV);
	else
	{
		free(env->value);
		env->value = ft_strdup(value);
	}
}

void	ft_print_export(t_shell *shell)
{
	t_env	*current;

	current = shell->env_lst;
	while (current)
	{
		printf("declare -x ");
		printf("%s=", current->key);
		printf("\"%s\"\n", current->value);
		current = current->next;
	}
}

void	ft_export(t_shell *shell, int *flag)
{
	char	*value;
	char	**tmp;
	int		i;

	*flag = 1;
	tmp = ft_split(shell->constrs->data, ' ');
	i = 0;
	if (!tmp[1])
		ft_print_export(shell);
	while (tmp[++i])
	{
		if (!ft_strchr(tmp[i], '='))
			return ;
		else
		{
			value = ft_strchr(tmp[i], '=') + 1;
			*(ft_strchr(tmp[i], '=')) = 0;
		}
		check_add(shell, shell->env_lst, tmp[i], value);
	}
}
