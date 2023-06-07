/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:55:15 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/07 15:56:11 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_shell *shell, int *flag)
{
	t_token *tokens;
	char *tmp;

	*flag = 1;
	tokens = shell->tokens->next;
	if (!tokens)
	{	
		printf("\n");
		return (0);
	}
	if (!ft_strncmp(tokens->data, "-n", 2))
		while(tokens)
		{
			tmp = ft_strtrim(tokens->data, "'\"");
			printf("%s", tmp);
			if (tokens->next && tokens->next->data[0] != '"' && tokens->next->data[0] != '\'')
				printf(" ");
			tokens = tokens->next;
		}
	else 
	{
		while(tokens)
		{
			tmp = ft_strtrim(tokens->data, "'\"");
			printf("%s", tmp);
			if (tokens->next && tokens->next->data[0] != '"' && tokens->next->data[0] != '\'')
				printf(" ");
			tokens = tokens->next;
		}
		printf("\n");
	}
	return (0);
}