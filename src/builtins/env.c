/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:39:04 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/12 15:27:28 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell, int *flag)
{
	t_env	*current;

	*flag = 1;
	current = shell->env_lst;
	while (current)
	{
		if (current->value)
		{
			printf("%s", current->key);
			printf("=%s\n", current->value);
		}
			current = current->next;
	}
}
