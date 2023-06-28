/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:02:00 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/19 19:53:21 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_const	*mylstlast(t_const *lst)
{
	if (!lst)
		return (0);
	while (lst -> next != 0)
		lst = lst -> next;
	return (lst);
}

t_const	*create_newnode(char *token, char *command)
{
	t_const	*newnode;

	newnode = malloc(sizeof(t_const));
	if (!newnode)
		return (0);
	newnode -> data = ft_strdup(token);
	newnode -> command = ft_strdup(command);
	newnode -> next = NULL;
	free(token);
	free(command);
	return (newnode);
}

void	constr_add_back(t_const **lst, t_const *new)
{
	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		new->prev = NULL;
		return ;
	}
	new->prev = mylstlast(*lst);
	mylstlast(*lst)->next = new;
}

void	ft_loop(char **tmp, char **str, t_token	**ptoken)
{
	*tmp = *str;
	if (*str[0])
	{
		*str = ft_strjoin(*str, " ");
		free(*tmp);
		*tmp = *str;
	}
	*str = ft_strjoin(*str, (*ptoken)->data);
	free(*tmp);
	*ptoken = (*ptoken)->next;
}

t_const	*create_constr(t_shell *shell)
{
	char		*str;
	t_token		*ptoken;
	char		*command;
	char		*tmp;

	ptoken = shell->tokens;
	while (ptoken)
	{
		command = NULL;
		str = ft_calloc(1, sizeof(char));
		while (ptoken && (ptoken->data[0] != '|' && ptoken->data[0] != '<'
				&& ptoken->data[0] != '>' && ft_strncmp(ptoken->data, "<<", 2)
				&& ft_strncmp(ptoken->data, ">>", 2)))
		{
			ft_loop(&tmp, &str, &ptoken);
		}
		if (ptoken)
		{
			command = ft_strdup(ptoken->data);
			ptoken = ptoken->next;
		}
		constr_add_back(&shell->constrs, create_newnode(str, command));
	}
	return (shell->constrs);
}
