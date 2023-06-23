/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:54:26 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/22 13:56:31 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char *isolate_str(char *str)
// {
//     int i;
//     int j;

//     i = 0;
//     while (str[i] != ' ')
//         i++;
//     while  (str[i] == ' ')
//         i++;
//     j = i;
//     while (str[i] != ' ' && str[i])
//         i++;
//     return (ft_substr(str, j, i));
// }

// static void	fill_file(char *overwrite, char *file)
// {
// 	int	fd;

// 	overwrite = isolate_str(overwrite);
// 	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY);
// 	write(fd, overwrite, ft_strlen(overwrite));
//     write(fd, "\n", 1);
// 	close(fd);
// }

// static void	append_to_file(char *overwrite, char *file)
// {
// 	int	fd;

// 	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0400 | 0200 | 0040 | 0004);
// 	write(fd, overwrite, ft_strlen(overwrite));
//     write(fd, "\n", 1);
// 	close(fd);
// }

#include <fcntl.h>
#include <unistd.h>

void redirect_output_echo(t_shell *shell, t_constr *tmp)
{
	char	*file;
	int		fd;
	char buffer[1024];
	ssize_t bytes_read;

	if (!ft_strncmp(tmp->command, ">", 2) || !ft_strncmp(tmp->command, ">>", 3))
		file = tmp->next->data;
	if (!ft_strncmp(tmp->command, ">", 2) || !ft_strncmp(tmp->command, ">>", 3))
	{
		int pipefd[2];
		pipe(pipefd);

		pid_t pid = fork();
		if (pid < 0)
			printf("ERROR REDIRECT");
		else if (pid == 0)
		{
			// child process
			close(pipefd[0]); //close the read end

			// redirect stdout to the write end
			dup2(pipefd[1], STDOUT_FILENO);

			if (!ft_strncmp(tmp->command, ">", 2))
				execute_command(shell, tmp->prev->data);
			else if (!ft_strncmp(tmp->command, ">>", 3))
				execute_command(shell, tmp->prev->data);

			exit(0); // exit child
		}
		else
		{
			//parent
			close(pipefd[1]); // close write end

			//open the output file and write the contents from pipe to file
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0)
				write(fd, buffer, bytes_read);
			close(fd);
			close(pipefd[0]);

			waitpid(pid, NULL, 0); //wait for child process to finish
		}
	}
}

void	redirect_output(t_shell *shell, t_constr *cmds)
{
	t_constr	*tmp;

	tmp = cmds;
	if (!tmp->next->data)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n",
			2);
		return ;
	}
	redirect_output_echo(shell, tmp);
}
