/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:58:14 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/09 17:13:09 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delnode(t_shell *shell, t_env *env)
{
	t_env	*tmp;

	tmp = shell->env_lst;
	while (tmp->next != env)
		tmp = tmp->next;
	tmp->next = env->next;
	free(env);
}

void	ft_unset(t_shell *shell, int *flag)
{
	t_token	*tmp;
	t_env	*env;

	*flag = 1;
	tmp = shell->tokens->next;
	if (!tmp)
		return ;
	while (tmp && tmp->data[0] != '|' && tmp->data[0] != '<' && 
		tmp->data[0] != '>' && ft_strncmp(tmp->data, "<<", 2) != 0 
			&& ft_strncmp(tmp->data, ">>", 2) != 0)
	{
		env = shell->env_lst;
		while (env)
		{
			if (!ft_strncmp(tmp->data, env->key, ft_strlen(env->key)))
				delnode(shell, env);
			env = env->next;
		}
		tmp = tmp->next;
	}

}