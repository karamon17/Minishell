/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:02:00 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/08 19:51:29 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_constr *mylstlast(t_constr *lst)
{
	if (!lst)
		return (0);
	while (lst -> next != 0)
		lst = lst -> next;
	return (lst);
}

t_constr *create_newnode(char *token, char *command)
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

void constr_add_back(t_constr **lst, t_constr *new)
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

int create_constr(t_shell *shell)
{
	t_constr *constr;
	t_constr *node;
	char *str;
	char *token;
	t_token *ptoken;
	char *command;
	char *tmp;

	ptoken = shell->tokens;
	token = ptoken->data;
	constr = NULL;
	while (ptoken)
	{
		command = NULL;
		str = ft_calloc(1, sizeof(char));
		while (ptoken && (token[0] != '|' && token[0] != '<' && token[0] != '>' && ft_strncmp(token, "<<", 2) != 0 && ft_strncmp(token, ">>", 2) != 0))
		{
			tmp = str;
			if (str[0])
			{
				str = ft_strjoin(str, " ");
				free(tmp);
				tmp = str;
			}
			str = ft_strjoin(str, token);
			free(tmp);
			ptoken = ptoken->next;
			if (ptoken)
				token = ptoken->data;
		}
		if (ptoken)
		{
			command = ft_strdup(token);
			ptoken = ptoken->next;
			if (ptoken)
				token = ptoken->data;
		}
		node = create_newnode(str, command);
		constr_add_back(&constr, node);
		free(str);
	}
	shell->constrs = constr;
	return (0);
}