/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:42:58 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/05 14:13:47 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(int *flag)
{
    char cwd[PATH_MAX];
	
	*flag = 1;
    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
        printf("%s\n", cwd);
    }
	else
	{
        perror("getcwd() error");
    }
}

