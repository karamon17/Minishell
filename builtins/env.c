/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:39:04 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/24 13:42:03 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_env(t_shell *shell)
{
    t_env *current;

	current = shell->env_lst;
	while (current)
	{
		printf("%s=", current->key);
		printf("%s\n", current->value);
		current = current->next;
	}
}
