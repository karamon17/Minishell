/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:36:20 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/10 17:16:57 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(t_shell *shell, char *name)
{
	t_env *current;
	
	current = shell->env_lst;
	while (current)
	{
		if (!ft_strncmp(current->key, name, ft_strlen(name)))
			return (current->value);
		current = current->next;
	}
	return (0);
}

char **env_to_2darray(t_shell *shell)
{
	t_env *current;
	int len;
	char *tmp;
	char **res;
	int i;

	len = 0;
	i = 0;
	current = shell->env_lst;
	while (current)
	{
		len++;
		current = current->next;
	}
	current = shell->env_lst;
	res = malloc((len + 1) * sizeof(char *));
	while (current)
	{
		res[i] = ft_strdup(current->key);
		tmp = res[i];
		res[i] = ft_strjoin(res[i], "=");
		free(tmp);
		tmp = res[i];
		res[i] = ft_strjoin(res[i], current->value);
		free(tmp);
		current = current->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}