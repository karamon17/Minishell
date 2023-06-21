/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:47:08 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/20 17:48:34 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_in_tokens(t_shell **shell)
{
	t_token	*tmp;

	tmp = (*shell)->tokens;
	while (tmp)
	{
		if (tmp->type != '\0')
		{
			if (tmp->type == 'E')
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	free_tokens(t_token	*tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (!tokens)
		return ;
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
	if (!constrs)
		return ;
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

void	ft_free_path(char **path)
{
	int	i;

	if (path == NULL)
		return ;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

// void    free_shell(t_shell *shell)
// {
//     free_tokens(shell->tokens);
//     free_env_list(shell);
//     free(shell);
//     exit (g_error_status);
// }