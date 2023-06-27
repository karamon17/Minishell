/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:00:26 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/27 14:00:28 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_setlvl(const char *name, char **envp, char *val)
{
    char    **tmp;
    char    *str;
    int     i;
    
    i = 0;
    tmp = envp;
    while (tmp[i] != NULL && ft_strncmp(name, tmp[i], 5))
        i++;
    if (!ft_strncmp(name, tmp[i], 5))
    {
        str = ft_substr(tmp[i], 0, 6);
        tmp[i] = ft_mystrjoin(str, val);
		free(val);
        return (0);
    }
    return (-1);
}

void	add_shlvl(char **envp)
{
    char	*shlvl;
	int		level;
	char	*newlevel;

	shlvl = getenv("SHLVL");
	newlevel = NULL;
    if (shlvl == NULL) 
        ft_setlvl("SHLVL", envp, "1");
	else
	{
       	level = ft_atoi(shlvl);
        level++;
		newlevel = ft_itoa(level);
	}
    	ft_setlvl("SHLVL", envp, newlevel);
}
