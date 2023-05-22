/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:36:20 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/22 17:45:41 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_getenv(t_minishell *shell, char *name)
{
	char **envp = shell->envp;
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, ft_strlen(name)))
			return (envp[i] + ft_strlen(name) + 1);
		i++;
	}
	return (0);
}

int getenvlen(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		i++;
	}
	return (i);
}

char **envdup(char **env)
{
	char **res;
	int len;
	int i;

	len = getenvlen(env);
	res = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		res[i] = ft_strdup(env[i]);
		i++;
	}
	env[i] = NULL;
	return(res);
}