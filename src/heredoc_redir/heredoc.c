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