/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:15:26 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/16 14:15:28 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define B_IN 0
# define PIPE 1
# define R_DIR 2
# define OPT 3
# define DELIM 4
# define TEXT 5
# define ENV 6

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

typedef struct s_token
{
    char        *data;
    int         type;
    struct s_token  *next;  
}               t_token;

typedef struct s_tree
{
    void            *data;
    int             type;
    struct s_tree   *left;
    struct s_tree   *right;
}               t_tree;

typedef struct s_env

{
    char            *name;
    char            *content;
    int             is_env;
    struct s_env    *next;
}           t_env;

typedef struct  s_table
{
    int state;
    int event;
    int action;
    int next;
    int minus;
}               t_table;

typedef struct s_shell
{
    struct s_token *tokens;
    struct s_tree  *cmd_tree;
}               t_shell;
#endif
