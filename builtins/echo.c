/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:55:15 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/15 13:56:07 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_sys_config *mini)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (mini->tokens->token[1])
	{
		if (ft_strcmp(mini->tokens->token[i], "-n") == 0 && i++)
			new_line = 0;
		while (mini->tokens->token[i] != NULL)
		{
			ft_printf("%s", mini->tokens->token[i]);
			if (mini->tokens->token[i + 1])
				ft_printf(" ");
			i++;
		}
	}
	if (new_line == 1)
		printf("\n");
	return (0);
}