/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:15:26 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/26 17:47:03 by gkhaishb         ###   ########.fr       */
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
# include <errno.h>

int	g_error_status;

typedef struct s_helper
{
	pid_t	pid;
	char	**argv;
	char	**env2darray;
	int		status;
}			t_helper;

typedef struct s_token
{
	char			*data;
	char			type;
	struct s_token	*next;
}	t_token;

typedef struct s_const
{
	char			*data;
	char			*command;
	int				fd[2];
	struct s_const	*prev;
	struct s_const	*next;
}	t_const;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
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
}	t_flag;

typedef struct s_shell
{
	struct s_token	*tokens;
	struct s_const	*constrs;
	struct s_env	*env_lst;
	int				fd;
	char			*heredoc_name;
	int				flag;
}	t_shell;

int		execute_builtin(t_shell *shell);
void	add_shlvl(char **envp);
char	*find_env_val(t_env *env_lst, char *key);
t_env	*ft_add_env_back(t_env *env_list, char *key, char *value);
void	get_env_var(t_env **env_lst, char **envp);
char	*ft_get_value(t_shell *shell, char *str, int *k);

t_token	*stugel(t_token *tokens);
t_token	*check_options(t_token *tmp);

t_token	*initialize_tokens(t_token *tokens);
int		grab_pipe(char *input, int i, t_token **new);
int		d_quotes(char *input, int i, t_token **new);
int		append_word(char *input, int i, t_token **new);
int		s_quotes(char *input, int i, t_token **new);
t_token	*first_parse(char *tmp, t_shell *shell, int i);

int		ft_strcmp(char *s1, char *s2);

t_token	*ft_new_token(char *content);
t_token	*ft_token_last(t_token *head);
void	ft_token_add_back(t_token **stack, t_token *new);
int		ft_token_size(t_token *head);
char	*double_strjoin(char *tmp, char *input, int *j);

void	is_b_in(t_token **head);
void	is_pipe(t_token **head);
void	is_env(t_token **head);

void	second_parse(t_token **tokens);
void	is_redir(t_token **head);
void	is_option(t_token **head);

void	ft_echo(t_shell *shell, int *flag, t_const *example);

char	*ft_getenv(t_shell *shell, char *name);
t_token	*env_check(t_shell *shell, t_token *tokens);
void	sigint_handler(int signum);
t_const	*create_constr(t_shell *shell);
char	**env_to_2darray(t_shell *shell);
void	ft_pipex(t_shell *shell);
char	*check_path(t_shell *shell);
void	ft_close_pipe(int fd[2]);
void	move_shell_tokens(t_shell *shell);
void	ft_cdprint_error(char *cmd);
void	ft_cdprint_error2(char *cmd);

int		quote_check(t_token *tokens);
void	free_shell(t_shell *shell);
void	free_tokens(t_token	*tokens);
void	free_env_list(t_shell *shell);
void	free_constrs(t_const	*constrs);

t_token	*delete_token(t_token **head, t_token *to_delete);

int		white_space_helper(char *input, int j, int in_q, int size);
char	*allocate_and_check_tmp(int size);
char	*set_tmp(char *input, int j, char *tmp);
int		update_in_q(char *input, int j, int in_q);
void	cut_spaces(t_token **tokens);
void	clean_shell(t_shell **shell);
int		parse_norm_helper(char *tmp, t_token *new, int i);
t_token	*kani_heredoc(t_shell **shell);
int		exec_heredoc(t_shell **shell, t_token *tokens);
char	*str_lower(char *str);
void	ft_free_path(char **path);
char	*ft_mystrjoin(char const *s1, char const *s2);
void	ft_oldpwd_notset(void);
void	ft_fork_error(t_const *constr);

int		ft_setlvl(const char *name, char **envp, char *val);
int		error_in_tokens(t_shell **shell);
void	ft_error_path(t_shell *shell);
char	*ft_mystrjoin2(char const *s1, char const *s2);
void	redirect_output(t_shell *shell, t_const *cmds);

char	*prev_node(t_token *head, t_token *token);

int		execute(t_shell *shell);
int		exec_comm(t_shell *shell, char *path);
void	ft_mainpipe(t_shell *shell, t_const *c);
void	pipex_helper(t_shell *shell);
void	ft_child(t_shell *shell, t_const *constr, int *pid);
void	ft_env(t_shell *shell, int *flag, t_const *example);
void	ft_unset(t_shell *shell, int *flag);
void	ft_export(t_shell *shell, int *flag, t_const *example);
void	ft_exit(t_shell *shell, int *flag, t_const *example);
void	ft_cd(t_shell *shell, t_const *example);
void	ft_pwd(int *flag, t_const *example);
int		file_check(t_const *example, int fd, int *flag);
t_token	*check_redirects(t_token *new);
int		heredoc_norm_helper(t_shell **shell, t_token **tmp);
int		check_next_node(t_token *tmp);
char	print_and_set_type(char type);
void	close_file(int fd);
void	export_helper(char *tmp, t_shell *shell, char *value, int *cat);
int		ft_exec_error(char *str, char **argv, char **env2darray);
int		check_builtin(t_shell *shell);
int		ft_checkletter(char *arg, int *cat);
void	check_add(t_shell *shell, char *key, char *value, int *cat);
void	ft_printerror(char *tmp, char *value);
char	*helper(char *result);
void	ft_print_error_red(char *cmd);
void	sigint_handler2(int signum);
void	cd_helper(t_shell *shell, t_token *token);
int		check_redirects_helper(t_token *tmp, int flag);
void	free_heredocs(t_shell **shell);
#endif
