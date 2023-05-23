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
# define ENV 5
# define HDOC 6

# include "lexer_1/lexer.h"
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
    struct s_token  *next;  
}               t_token;

typedef struct s_tree
{
    void            *data;
    struct s_tree   *left;
    struct s_tree   *right;
}               t_tree;

typedef struct s_env
{
    struct s_env	*next;
	char			*key;
    char			**tmp;
	char			*value;
    char			*tmp0;
	char			*tmp1;
    char			*tmp2;
	int				flag;
	int				i;
	int				pop;
	int				exflag;
}	t_env;

enum e_flag
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
}   t_flag;

typedef struct s_shell
{
    struct s_tree   *ast;
    struct s_token  *tokens;
    struct s_env    *env_lst;
    int             err_stat;
}               t_shell;

t_tree* buildAST(t_token **tokens);
void printAST(t_tree *root);
void    get_env_var(t_env **env_lst, char **envp);
//void    printENV(t_env *env_lst);
int	ft_atoi(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
void    aveletsnel_shvl(t_env *env_lst);
char    *find_env_val(t_env *env_lst, char *key);
t_env	*ft_add_new_env(char *key, char *value, int flag);
t_env	*ft_add_env_back(t_env *env_list, char *key, char *value, int flag);
void    get_env_var(t_env **env_lst, char **envp);
size_t  ft_strlen(const char *str);
#endif
