/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:55:15 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/25 12:31:12 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_shell *shell)
{
	t_token *tokens;

	tokens = shell->tokens->next;
	if (!tokens)
		printf("\n");
	if (!ft_strncmp(tokens->data, "-n", 2))
		while(tokens)
		{
			printf(tokens->data);
			tokens = tokens->next;
		}
	return (0);
}