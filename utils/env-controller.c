/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:36:20 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/23 13:34:13 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_getenv(t_shell *shell, char *name)
{
	while (shell->env_lst)
	{
		if (!ft_strncmp(shell->env_lst->key, name, ft_strlen(name)))
			return (shell->env_lst->value);
		shell->env_lst = shell->env_lst->next;
	}
	return (0);
}

// int getenvlen(char **env)
// {
// 	int i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char **envdup(char **env)
// {
// 	char **res;
// 	int len;
// 	int i;

// 	len = getenvlen(env);
// 	res = malloc(sizeof(char *) * (len + 1));
// 	i = 0;
// 	while (i < len)
// 	{
// 		res[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	env[i] = NULL;
// 	return(res);
// }