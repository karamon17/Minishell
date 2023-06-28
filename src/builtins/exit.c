/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:16:45 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/27 16:04:09 by gkhaishb         ###   ########.fr       */
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
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (0);
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

void	ft_exit(t_shell *shell, int *flag, t_constr *example)
{

	shell->fd = 1;
	*flag = 1;
	shell->fd = file_check(example, shell->fd, &shell->flag);
	printf("exit\n");
	if (!shell->tokens->next || !ft_strncmp(shell->tokens->next->data, "|", 2))
		exit(0);
	else if ((shell->tokens->next && !shell->tokens->next->next && \
			!check(shell->tokens->next->data)) || (shell->tokens->next && \
			!ft_strncmp(shell->tokens->next->data, "|", 2)) || \
			(shell->tokens->next->next && !check(shell->tokens->next->data) && \
			!ft_strncmp(shell->tokens->next->next->data, "|", 2)))
		exit(ft_atoi(shell->tokens->next->data));
	else if (shell->tokens->next && check(shell->tokens->next->data))
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(shell->tokens->next->data, 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		exit(255);
	}
	else
	{
		g_error_status = 1;
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
	}
	if (shell->fd != 1)
		close (shell->fd);
	return ;
}
