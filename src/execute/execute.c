/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:11:11 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/03 16:56:36 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_command(t_shell *shell, char *path)
{
	pid_t pid;
	
	pid = fork();
	//printf("%s\n", shell->constrs->data);
	if (pid == 0)
	{
		execve(path, ft_split(shell->constrs->data, ' '), env_to_2darray(shell));
	}
	else
	{
		wait(NULL);
	}
	return (0);
}

void free_path(char **path)
{
	int i = 0;
	
	while (path[i])
		free(path[i++]);
	free(path);
}

int	execute(t_shell *shell)
{
	char **path;
	char *tmp;
	int i;

	path = ft_split(ft_getenv(shell, "PATH"), ':');
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		tmp = path[i];
		path[i] = ft_strjoin(path[i], shell->tokens->data);
		free(tmp);
		i++;
	}
	i = 0;
	while (path[i])
	{
		//printf("this is my print %s\n", path[i]);
		if (!access(path[i], X_OK))
			break;
		i++;
	}
	execute_command(shell, path[i]);
	free_path(path);
	return (0);
}
