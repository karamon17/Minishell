/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:36:20 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/30 17:38:42 by gkhaishb         ###   ########.fr       */
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
