/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:55:15 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/14 14:10:47 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_withoutn(t_token	*tokens)
{
	while (tokens && tokens->data[0] != '|' && tokens->data[0] != '<'
		&& tokens->data[0] != '>' && ft_strncmp(tokens->data, "<<", 2)
		!= 0 && ft_strncmp(tokens->data, ">>", 2) != 0)
	{
		printf("%s", tokens->data);
		if (tokens->next && tokens->next->data[0] != '|')
			printf(" ");
		tokens = tokens->next;
	}
	printf("\n");
}

void	ft_echo(t_shell *shell, int *flag)
{
	t_token	*tokens;

	*flag = 1;
	tokens = shell->tokens->next;
	if (!tokens)
	{	
		printf("\n");
		return ;
	}
	if (!ft_strncmp(tokens->data, "-n", 3))
	{	
		tokens = tokens->next;
		while (tokens)
		{
			printf("%s", tokens->data);
			if (tokens->next && tokens->next->data[0] != '|')
				printf(" ");
			tokens = tokens->next;
		}
	}
	else
		ft_withoutn(tokens);
}
