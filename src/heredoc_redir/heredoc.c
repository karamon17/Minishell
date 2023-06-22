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

void	print_and_set_type(char *type)
{
	ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
	type[0] = 'E';
}

void	write_helper(int tmp_fd, char *line)
{
	write(tmp_fd, line, ft_strlen(line));
	write(tmp_fd, "\n", 1);
}

char	*gen_random_name(void)
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
	else if (!ft_strncmp(tmp->next->data, "<<", 3) || \
	!ft_strncmp(tmp->next->data, "<", 2))
		return (-1);
	else if (!ft_strncmp(tmp->next->data, ">>", 3) || \
	!ft_strncmp(tmp->next->data, ">", 2))
		return (-1);
	return (0);
}

int	exec_heredoc(t_token *tokens)
{
	int		tmp_fd;
	char	*random_name;
	char	*limit;
	char	*line;
	char	*file_name;

	random_name = NULL;
	limit = tokens->next->data;
    if (random_name)
     	free(random_name);
    random_name = gen_random_name();
	file_name = ft_strdup("_heredoc_tmp");
	file_name = ft_strjoin(random_name, file_name);
	printf("[%s]\n", file_name);
	tmp_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		ft_putstr_fd("heredoc error\n", 2);
		return (-1);
	}
	while ((ft_strncmp(limit, line = readline("> "), ft_strlen(limit)) != 0))
		write_helper(tmp_fd, line);
	free(random_name);
	free(file_name);
	close(tmp_fd);
	return (0);
}

void	kani_heredoc(t_shell **shell)
{
	t_token	*tmp;

	tmp = (*shell)->tokens;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, "<<", 3))
		{
			if (check_next_node(tmp) == -1)
			{
				print_and_set_type(&tmp->type);
				break ;
			}
			if (exec_heredoc(tmp) == -1)
			{
				print_and_set_type(&tmp->type);
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