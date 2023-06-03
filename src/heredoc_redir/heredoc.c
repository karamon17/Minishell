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

// void    heredoc(t_constr *new)
// {
//     t_constr *tmp;
//     int redir_fd; //file to redirect data to or create if does not exist

//     while (ft_strncmp(tmp->command, "<<"))
//         tmp = tmp->next;
//     while (ft_strncmp(tmp->command, "hdoc_delim"))
//     {
//         redir_fd = open(tmp->data, O_CREAT | O_EXCL | O_WRONLY); //create file if does not exist | erase previous data | ope and read write only
//         dup2(redir_fd, STDOUT_FILENO); //take data from redir fd and send to the stdout
//         tmp = tmp->next;
//     }
// }
