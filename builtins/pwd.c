/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:42:58 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/22 13:21:40 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd()
{
    char cwd[PATH_MAX];
	
    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
        printf("%s\n", cwd);
    }
	else
	{
        perror("getcwd() error");
    }
}

