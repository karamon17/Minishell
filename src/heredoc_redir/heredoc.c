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

void    kani_heredoc(t_shell **shell)
{
    int         i;
    t_token    *tmp;

    i = 0;
    tmp = (*shell)->tokens;
    while (tmp)
    {
        if (!ft_strncmp(tmp->data, "<<", 3))
            i++;
        tmp = tmp->next;
    }
    tmp = (*shell)->tokens;
    while (tmp && i > 0)
    {
        if (!ft_strncmp(tmp->data, "<<", 3))
        {
            i = exec_heredoc(tmp, i);
            delete_token(&(*shell)->tokens, tmp);
            if (ft_strncmp(tmp->next->data, "<<", 3))
                delete_token(&(*shell)->tokens, tmp->next);
        }
        tmp = tmp->next;
    }
}

int    exec_heredoc(t_token *tokens, int i)
{
    int     tmp_fd;
    char    *limit;
    char    *line;
    //int     pid;

    limit = tokens->next->data;
    tmp_fd = open("tmp_file", O_CREAT, O_APPEND, O_WRONLY |O_SYNC, S_IRUSR | S_IWUSR, 777);
    if (tmp_fd == -1)
    {
        printf("error\n");
        exit(1);
    }
    //pid = fork();
    //if (pid == 0)
    while ((ft_strncmp(limit, line = readline("> "), ft_strlen(limit)) != 0))
    {
        write(tmp_fd, line, ft_strlen(line));
        write(tmp_fd, "\n", 1);
    }
    close(tmp_fd);
    return (i - 1);
}