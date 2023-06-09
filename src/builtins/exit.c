/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:16:45 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/09 16:37:34 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str == '0')
		str++;
	if (ft_strlen(str) >= 20)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int	ft_exit(t_shell *shell, int *flag)
{
	*flag = 1;
	printf("exit\n");
	if (!shell->tokens->next)
		exit(0);
	else if (shell->tokens->next && check(shell->tokens->next->data))
	{
		printf("minishell: exit: %s numeric argument required\n",
			shell->tokens->next->data);
		exit(1);
	}
	else if (shell->tokens->next && !shell->tokens->next->next)
		exit(ft_atoi(shell->tokens->next->data));
	else
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	return (0);
}
