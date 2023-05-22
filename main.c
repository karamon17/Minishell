/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:57:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/22 18:58:42 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void    ft_error_exit(char *str)
{
    while (*str)
        write(2, str++, 1);
    exit(1);
}

void    shell_loop(t_token **tokens)
{
    t_tree      *ast;
    t_token     *check;
    char        *input;
	(void)tokens;
    while ((input = readline("Minishell $>")) != NULL)
    {
        add_history(input);
        if (ft_strncmp(input, "exit", 4) == 0)
            break ;
        //check = first_parse(input, *tokens);
        free(input);
        ast = buildAST(&check);
        //printAST(ast);
        //parse_ast(ast);
        free(ast);
    }
}

t_token    *initalize_tokens(t_token **tokens)
{
    if ((*tokens) == NULL)
        (*tokens) = malloc(sizeof(t_token));
    if (!tokens)
        ft_error_exit("Malloc Error: Token Struct");
    (*tokens)->next = NULL;
    (*tokens)->data = NULL;
    return (*tokens);
}

int main(int ac, char **av, char **env)
{
    t_token *tokens;
	t_minishell *shell;
    
    (void)av;
    tokens = NULL;
    if (ac > 1)
         exit (1);
	shell = malloc(sizeof(t_minishell));
	shell->envp = envdup(env);
    tokens = initalize_tokens(&tokens);
    shell_loop(&tokens);
	execute_builtin(shell, tokens);
    return (0);
}
