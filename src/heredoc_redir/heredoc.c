/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:12:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/02 14:12:32 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    kani_hrdoc(t_shell *shell)
{
    while (shell->constr)
    {
        if (ft_strcmp(shell->constr->command, "<<"))
            shell->hrdoc_cnt++;
    }
}

void    heredoc(t_constr *new)
{
   int  fd;
   char *name;
   char *limit;
   t_constr *head;

   name = ft_strdup("");
   fd = -1;
   head = new;
   limit = head->next->data;
   head = head->next->next;
   while (1)
   {
        name = f
        head = head->next;
   }
}
