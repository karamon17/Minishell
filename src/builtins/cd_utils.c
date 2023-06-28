/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:24:10 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/20 16:32:35 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cdprint_error2(char *cmd)
{
	g_error_status = 1;
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	ft_print_error_red(char *cmd)
{
	g_error_status = 1;
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	ft_cdprint_error(char *cmd)
{
	g_error_status = 1;
	if (errno == 13)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
}

void	ft_oldpwd_notset(void)
{
	g_error_status = 1;
	ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
}

void	cd_helper(t_shell *shell, t_tokens *token)
{
	char	*to_free;

	to_free = ft_getenv(shell, "PWD");
	if (token && token->data[0] == '-' && !token->data[1] && !g_error_status)
		printf("%s\n", to_free);
	free(to_free);
	close_file(shell->fd);
}
