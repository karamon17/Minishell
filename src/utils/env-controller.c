/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:36:20 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/19 15:02:27 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_shell *shell, char *name)
{
	t_env	*current;

	current = shell->env_lst;
	while (current)
	{
		if (!ft_strncmp(current->key, name, ft_strlen(name)))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (0);
}

int	ft_envlen(t_env	*current)
{
	int		len;

	len = 0;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

char	**env_to_2darray(t_shell *shell)
{
	t_env	*current;
	char	*tmp;
	char	**res;
	int		i;

	i = 0;
	current = shell->env_lst;
	res = malloc((ft_envlen(current) + 1) * sizeof(char *));
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
