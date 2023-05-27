/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:58:14 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/24 17:35:56 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void delnode(t_shell *shell, t_env *env)
{
	t_env *tmp;

	tmp = shell->env_lst;
	while (tmp->next != env)
		tmp = tmp->next;
	tmp->next = env->next;
	free(env);
}

void ft_unset(t_shell *shell)
{
	t_token *tmp;
	t_env *env;

	tmp = shell->tokens;
	env = shell->env_lst;
	while (tmp)
	{
		while (env)
		{
			if (!ft_strncmp(tmp->next->data, env->key, ft_strlen(env->key)))
				delnode(shell, env);
			env = env->next;
		}
		tmp = tmp->next;
	}

}