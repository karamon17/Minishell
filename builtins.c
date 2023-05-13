/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:42:58 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/05/13 17:43:02 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **args)
{
    if (args[1] == NULL)
    {
        chdir(getenv("HOME"));
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("cd");
        }
    }
    return (1);
}

int ft_echo(char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
    return (1);
}

int ft_exit(char **args)
{
    exit(0);
}

void execute_pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
    }
}

