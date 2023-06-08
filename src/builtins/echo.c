/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:55:15 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/30 17:37:36 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_shell *shell)
{
	t_token *tokens;

	tokens = shell->tokens->next;
	if (!tokens)
	{	
		printf("\n");
		return (0);
	}
	if (!ft_strncmp(tokens->data, "-n", 2))
		while(tokens)
		{
			printf("%s", tokens->data);
			if (tokens->next)
				printf(" ");
			tokens = tokens->next;
		}
	else 
	{
		while(tokens)
		{
			printf("%s", tokens->data);
			if (tokens->next)
				printf(" ");
			tokens = tokens->next;
		}
		printf("\n");
	}
	return (0);
}