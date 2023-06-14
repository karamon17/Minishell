/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:47:08 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 18:22:59 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token	*tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tokens->next != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->data);
		free(tmp);
	}
	free(tokens->data);
	free(tokens);
}

void	free_constrs(t_constr	*constrs)
{
	t_constr	*tmp;

	tmp = constrs;
	while (constrs->next != NULL)
	{
		tmp = constrs;
		constrs = constrs->next;
		free(tmp->data);
		free(tmp->command);
		free(tmp);
	}
	free(constrs->data);
	free(constrs->command);
	free(constrs);
}

void	free_env_list(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env_lst;
	if (!tmp)
		return ;
	while (shell->env_lst->next != NULL)
	{
		tmp = shell->env_lst;
		shell->env_lst = shell->env_lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free((shell)->env_lst->key);
	free((shell)->env_lst->value);
	free((shell)->env_lst);
}

void    free_shell(t_shell *shell)
{
    free_tokens(shell->tokens);
    free_env_list(shell);
    free(shell);
    exit (g_error_status);
}