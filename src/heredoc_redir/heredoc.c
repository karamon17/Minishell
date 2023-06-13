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

// char    *gen_random_name(void)
// {
//     char    buffer[4];
//     int     fd;
    
//     fd = open("/dev/random", O_RDONLY);
// 	if (fd < -1)
// 		return (-1);
// 	read(fd, buff, 4);
// 	nbr = *(int *)buff;
// 	if (nbr < 0)
// 		nbr++;
// 	if (nbr < 0)
// 		nbr = nbr * (-1);
// 	return ('a' + nbr % 26);
// }

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
            tmp = tmp->next;
            if (ft_strncmp(tmp->data, "<<", 3))
                delete_token(&(*shell)->tokens, tmp);
        }
        tmp = tmp->next;
    }
}

int    exec_heredoc(t_token *tokens, int i)
{
    int     tmp_fd;
    char    random_name[] = "tmp_file";
    char    *limit;
    char    *line;

    limit = tokens->next->data;
    // if (random_name)
    //     free(readom_name);
    //random_name = gen_random_name();
    tmp_fd = open(random_name, O_CREAT, O_APPEND, O_EXCL | O_RDWR , 0644);
    if (tmp_fd == -1)
    {
        printf("error\n");
        exit(1);
    }
    while ((ft_strncmp(limit, line = readline("> "), ft_strlen(limit)) != 0))
    {
        write(tmp_fd, line, ft_strlen(line));
        write(tmp_fd, "\n", 1);
    }
    close(tmp_fd);
    return (i - 1);
}