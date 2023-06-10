/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:12:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/08 19:33:03 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    kani_hrdoc(t_shell *shell)
// {
//     while (shell->constr)
//     {
//         if (ft_strcmp(shell->constr->command, "<<"))
//             shell->hrdoc_cnt++;
//     }
// }

void    exec_heredoc(t_token *tokens)
{
    int     tmp_fd;
    char    *limit;
    char    *line;
    int     id;

    limit = tokens->next->data;
    tmp_fd = open("tmp_file", O_CREAT, O_APPEND, O_WRONLY);
    if (tmp_fd == -1)
    {
        printf("error\n");
        exit(1);
    }
    id = fork();
    while ((ft_strncmp(limit, line, ft_strlen(limit)) != 0))
    {
        line = readline("> ");
        write(tmp_fd, line, ft_strlen(line));
    }
    while (wait(&id) != -1)
        ;
}

// void    heredoc(t_constr *new)
// {
//    int  fd;
//    char *name;
//    char *limit;
//    t_constr *head;

//    name = ft_strdup("");
//    fd = -1;
//    head = new;
//    limit = head->next->data;
//    head = head->next->next;
//    while (1)
//    {
//         name = f
//         head = head->next;
//    }
// }