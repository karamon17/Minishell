/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:15:26 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/08 19:38:07 by gkhaishb         ###   ########.fr       */
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

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <curses.h>
# include <term.h>
# include <ctype.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cnt
{
	int	i;
	int	singles;
	int	doubles;
}			t_cnt;

typedef struct s_token
{
    char        *data;
	char		type;	
    struct s_token  *next;  
}               t_token;

typedef struct s_constr
{
    char        *data;	
	char        *command;
	int			fd[2];
	struct s_constr *prev;
    struct s_constr  *next;  
}               t_constr;

typedef struct s_env
{
    struct s_env	*next;
	char			*key;
    char			*tmp;
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
	ENVV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
}   t_flag;

typedef struct s_shell
{
    struct s_token  *tokens;
	struct s_constr  *constrs;
    struct s_env    *env_lst;
    int             err_stat;
}               t_shell;

int	execute_builtin(t_shell *shell);
void    aveletsnel_shvl(t_env *env_lst);
char    *find_env_val(t_env *env_lst, char *key);
t_env	*ft_add_new_env(char *key, char *value, int flag);
t_env	*ft_add_env_back(t_env *env_list, char *key, char *value, int flag);
void    get_env_var(t_env **env_lst, char **envp);
size_t  ft_strlen(const char *str);

t_token *stugel(t_token *tokens);
t_token *check_options(t_token *tmp);

t_token    *initialize_tokens(t_token *tokens);
int         grab_pipe(char *input, int i, t_token **new);
int         d_quotes(char *input, int i, t_token **new);
int         append_word(char *input, int i, t_token **new);
int         s_quotes(char *input, int i, t_token **new);
t_token	*first_parse(t_shell *shell, char *input, int i);

int	        ft_strcmp(char *s1, char *s2);

t_token	    *ft_new_token(char *content);
t_token	    *ft_token_last(t_token *head);
void	    ft_token_add_back(t_token **stack, t_token *new);
int	        ft_token_size(t_token *head);
char        *double_strjoin(char *tmp, char *input, int *j);

void    is_b_in(t_token **head);
void    is_pipe(t_token **head);
void    is_env(t_token **head);

void    second_parse(t_token **tokens);
void    is_redir(t_token **head);
void    is_option(t_token **head);

void ft_pwd(int *flag);
void 	ft_env(t_shell *shell, int *flag);
int		ft_exit(t_shell *shell, int *flag);
void 	ft_unset(t_shell *shell, int *flag);
int 	ft_export(t_shell *shell, int *flag);
int 	ft_echo(t_shell *shell, int *flag);
int		ft_cd(t_shell *shell, int *flag);
char 	*ft_getenv(t_shell *shell, char *name);
t_token *env_check(t_shell *shell, t_token *tokens);
void	sigint_handler(int signum);
int	execute(t_shell *shell);
int create_constr(t_shell *shell);
char **env_to_2darray(t_shell *shell);
void ft_pipex(t_shell *shell);
char *check_path(t_shell *shell);
void	ft_close_pipe(int fd[2]);

int			quote_check(t_token *tokens);
void		free_shell(t_shell **shell);

int    exec_heredoc(t_token *tokens, int i);
void	delete_token(t_token **head, t_token *to_delete);
void    redirect_output(t_constr *cmds);
void    kani_heredoc(t_shell **shell);
#endif
