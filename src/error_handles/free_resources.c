/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:47:08 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/08 19:32:32 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_tokens(t_shell **shell)
{
    t_token    *tmp;

    tmp = (*shell)->tokens;
    while (tmp != NULL)
    {
        tmp = (*shell)->tokens;
        (*shell)->tokens = (*shell)->tokens->next;
        free(tmp);
    }
}

void    free_env_list(t_shell **shell)
{
    t_env *tmp;

    tmp = (*shell)->env_lst;
    while (tmp != NULL)
    {
        tmp = (*shell)->env_lst;
        (*shell)->env_lst = (*shell)->env_lst->next;
        free(tmp);
    }
}

void    free_shell(t_shell **shell)
{
    int tmp;

    tmp = (*shell)->err_stat;
    free_tokens(shell);
    free_env_list(shell);
    free((*shell));
    exit (tmp);
}

void    ft_error_exit(char *str)
{
    while (*str)
        write(2, str++, 1);
}