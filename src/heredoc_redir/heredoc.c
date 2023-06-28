/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:59:48 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/27 13:59:49 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_helper(int tmp_fd, char *line, char *str, int flag)
{
	if (flag == 1)
	{
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	else if (flag == 0)
	{
		free(str);
		free(line);
		close(tmp_fd);
	}
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
		nbr = nbr * (-1);
	*name = ('a' + nbr % 26);
	return (name);
}

int	check_next_node(t_token *tmp)
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

int	exec_heredoc(t_shell **shell, t_token *tokens)
{
	int		tmp_fd;
	char	*limit;
	char	*line;
	char	*file_name;

	if (tokens->next)
		limit = tokens->next->data;
	file_name = ft_mystrjoin2(gen_random_name(), ft_strdup("_heredoc_tmp"));
	tmp_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		ft_putstr_fd("heredoc error\n", 2);
		return (-1);
	}
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline(">");
		if (!line || (line && !ft_strncmp(limit, line, ft_strlen(limit))))
			break ;
		heredoc_helper(tmp_fd, line, NULL, 1);
	}
	(*shell)->heredoc_name = ft_strdup(file_name);
	heredoc_helper(tmp_fd, line, file_name, 0);
	return (0);
}

t_token	*kani_heredoc(t_shell **shell)
{
	t_token	*tmp;
	int		flag;

	flag = 0;
	tmp = (*shell)->tokens;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, "<<", 3))
		{
			flag = heredoc_norm_helper(shell, &tmp);
			if (flag == -1)
				break ;
			tmp = delete_token(&(*shell)->tokens, tmp);
			if (tmp->data)
				tmp = delete_token(&(*shell)->tokens, tmp);
		}
		if (tmp)
			tmp = tmp->next;
	}
	if (flag == 1)
		return (tmp);
	else
		return ((*shell)->tokens);
}
