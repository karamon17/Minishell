/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:16:45 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/15 17:04:18 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_longlong(char *str)
{
	int					i;
	unsigned long long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (res > LONG_MAX)
			return (1);
	}
	return (0);
}

int	check(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str == '0')
		str++;
	if (ft_check_longlong(str) || ft_strlen(str) >= 20)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

void	ft_exit(t_shell *shell, int *flag)
{
	*flag = 1;
	printf("exit\n");
	if (!shell->tokens->next)
		exit(0);
	else if (shell->tokens->next && check(shell->tokens->next->data))
	{
		ft_putstr_fd("Minishell : exit: ", 2);
		ft_putstr_fd(shell->tokens->next->data, 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		exit(255);
	}
	else if (shell->tokens->next && !shell->tokens->next->next)
		exit(ft_atoi(shell->tokens->next->data));
	else
	{
		g_error_status = 1;
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
	}
	return ;
}
