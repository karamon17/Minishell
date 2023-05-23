/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:35:11 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/23 16:11:19 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
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

t_token    *initialize_tokens(t_token *tokens);
//lexer_1/lex_split_first.c
int         grab_pipe(char *input, int i, t_token **new);
int         d_quotes(char *input, int i, t_token **new);
int         append_word(char *input, int i, t_token **new);
int         s_quotes(char *input, int i, t_token **new);
t_token    *first_parse(char *input, t_token *tokens);

//lexer_1/lex_utils.c
int	        ft_strcmp(char *s1, char *s2);
char	    *ft_substr(char const *s, unsigned int start, size_t len);
size_t      ft_strlen(const char *str);
char	    *ft_strjoin(char const *s1, char const *s2);

//lexer_1/token_list_utils.c
t_token	    *ft_new_token(char *content);
t_token	    *ft_token_last(t_token *head);
void	    ft_token_add_back(t_token **stack, t_token *new);
int	        ft_token_size(t_token *head);
char        *double_strjoin(char *tmp, char *input, int *j);

//lexer_2/data_assignment_1.c
void    is_b_in(t_token **head);
void    is_pipe(t_token **head);
void    is_env(t_token **head);

//lexer2
void    second_parse(t_token **tokens);
void    is_redir(t_token **head);
void    is_option(t_token **head);
#endif