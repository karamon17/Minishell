/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:31:45 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/24 19:06:10 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_export(t_shell *shell)
{
	t_token *tmp;
	t_env *env;
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
	ft_add_env_back(env, tmp->data, value, ENV);
	return (0);
}