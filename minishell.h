/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:15:26 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/22 17:45:58 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define B_IN 0
# define PIPE 1
# define R_DIR 2
# define OPT 3
# define DELIM 4
# define ARGUMENT 5
# define ENV 6
# define HDOC 7

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <curses.h>
# include <term.h>
# include <ctype.h>
# include "struct.h"
# include "libft/libft.h"

typedef struct s_token
{
    char        *data;
    struct s_token  *next;  
}               t_token;

typedef struct s_tree
{
    void            *data;
    struct s_tree   *left;
    struct s_tree   *right;
}               t_tree;

t_tree* buildAST(t_token **tokens);
void printAST(t_tree *root);
int	ft_cd(t_minishell *shell, t_token *token);
int	execute_builtin(t_minishell *shell, t_token *token);
char *ft_getenv(t_minishell *shell, char *name);
char **envdup(char **env);

#endif
