/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:42:58 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/12 17:14:35 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(int *flag, t_const *example)
{
	char	cwd[PATH_MAX];
	int		fd;
	int		chk_flg;

	chk_flg = 1;
	fd = 1;
	*flag = 1;
	if (example->command && example->command[0] == '<')
		fd = file_check(example, fd, &chk_flg);
	if (fd == -1)
		return ;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		g_error_status = 1;
		perror("getcwd() error");
	}
	if (fd != 1)
		close(fd);
}
