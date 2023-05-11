/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:35:11 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/09 19:35:13 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

typedef struct s_token
{
    void        *data;
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

t_token *ft_new_token(char *content);
t_token *ft_token_last(t_token *head);
void    ft_token_add_back(t_token **stack, t_token *new);
int	    ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
#endif
