/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:22:11 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/15 11:51:05 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *gen_random_name(void)
{
	char			buff[4];
	char			*name;
	int				fd;
	int				nbr;

	name = ft_calloc(1, sizeof(char));
	fd = open("/dev/urandom", O_RDONLY);
 	if (fd < -1)
 		return ("ERROR");
 	read(fd, buff, 4);
 	nbr = *(int *)buff;
 	if (nbr < 0)
 		nbr++;
 	if (nbr < 0)
	{
 		nbr = nbr * (-1);
		*name = ('a' + nbr % 26);
	}
 	return (name);
 }

static int	check_next_node(t_token *tmp)
{
	if (tmp->next == NULL || tmp->next->data == NULL)
		return (-1);
	else if (!ft_strncmp(tmp->next->data, "<<", 3) || !ft_strncmp(tmp->next->data, "<", 2))
		return (-1);
	else if (!ft_strncmp(tmp->next->data, ">>", 3) || !ft_strncmp(tmp->next->data, ">", 2))
		return (-1);
	return (0);
}

static	int	count_heredoc(t_shell **shell, int i)
{
	t_token *tmp;

	tmp = (*shell)->tokens;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, "<<", 3))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	kani_heredoc(t_shell **shell)
{
	int		i;
	t_token	*tmp;

	i = count_heredoc(shell, 0);
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
			if (check_next_node(tmp) == -1)
			{
				ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
				tmp->type = 'E';
				break ;
			}
			i = exec_heredoc(tmp, i);
			if (i == -1)
			{
				ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
				tmp->type = 'E';
				break ;
			}
			delete_token(&(*shell)->tokens, tmp);
			tmp = tmp->next;
			if (ft_strncmp(tmp->data, "<<", 3))
				delete_token(&(*shell)->tokens, tmp);
		}
		tmp = tmp->next;
	}
}

int	exec_heredoc(t_token *tokens, int i)
{
	int		tmp_fd;
	char	*random_name;
	char	*limit;
	char	*line;

	random_name = NULL;
	limit = tokens->next->data;
    if (random_name)
     	free(random_name);
    random_name = gen_random_name();
	tmp_fd = open(random_name, O_CREAT | O_APPEND | O_EXCL | O_RDWR, 0400 | 0200 | 0040 | 0004);
	if (tmp_fd == -1)
	{
		ft_putstr_fd("heredoc error\n", 2);
		return (-1);
	}
	while ((ft_strncmp(limit, line = readline("> "), ft_strlen(limit)) != 0))
	{
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
	}
	close(tmp_fd);
	return (i - 1);
}
