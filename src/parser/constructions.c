/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:02:00 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/13 19:36:15 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_constr	*mylstlast(t_constr *lst)
{
	if (!lst)
		return (0);
	while (lst -> next != 0)
		lst = lst -> next;
	return (lst);
}

t_constr	*create_newnode(char *token, char *command)
{
	t_constr	*newnode;

	newnode = malloc(sizeof(t_constr));
	if (!newnode)
		return (0);
	newnode -> data = ft_strdup(token);
	newnode -> command = ft_strdup(command);
	newnode -> next = 0;
	return (newnode);
}

void	constr_add_back(t_constr **lst, t_constr *new)
{
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
		return ;
	}
	new->prev = mylstlast(*lst);
	mylstlast(*lst)->next = new;
}

t_constr	*create_constr(t_shell *shell)
{
	t_constr	*constr;
	char		*str;
	t_token		*ptoken;
	char		*command;
	char		*tmp;

	ptoken = shell->tokens;
	constr = NULL;
	while (ptoken)
	{
		command = NULL;
		str = ft_calloc(1, sizeof(char));
		while (ptoken && (ptoken->data[0] != '|' && ptoken->data[0] != '<'
				&& ptoken->data[0] != '>' && ft_strncmp(ptoken->data, "<<", 2)
				!= 0 && ft_strncmp(ptoken->data, ">>", 2) != 0))
		{
			tmp = str;
			if (str[0])
			{
				str = ft_strjoin(str, " ");
				free(tmp);
				tmp = str;
			}
			str = ft_strjoin(str, ptoken->data);
			free(tmp);
			ptoken = ptoken->next;
		}
		if (ptoken)
		{
			command = ft_strdup(ptoken->data);
			ptoken = ptoken->next;
		}
		constr_add_back(&constr, create_newnode(str, command));
		free(str);
	}
	shell->constrs = constr;
	return (shell->constrs);
}
