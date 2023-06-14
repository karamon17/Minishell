/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:24:10 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/12 18:49:44 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cdprint_error2(char *cmd)
{
	g_error_status = 1;
	ft_putstr_fd("Minishell : cd: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	ft_cdprint_error(char *cmd)
{
	g_error_status = 1;
	if (errno == 13)
	{
		ft_putstr_fd("Minishell : cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		ft_putstr_fd("Minishell : cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
}
