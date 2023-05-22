/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:57:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/15 16:54:06 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void    ft_error_exit(char *str)
{
    while (*str)
        write(2, str++, 1);
}

void    shell_loop(t_shell **shell)
{
    //t_token     *check;
    char        *input;

    while ((input = readline("Minishell $>")) != NULL && (*shell)->err_stat == 0)
    {
        add_history(input);
        if (ft_strcmp(input, "exit") == 0)
            break ;
        (*shell)->tokens = first_parse(input, (*shell)->tokens);
        free(input);
        (*shell)->ast = buildAST(&(*shell)->tokens);
        printAST((*shell)->ast);
        //parse_ast(ast);
        free((*shell)->ast);
    }
}

t_token *initialize_tokens(t_token *tokens)
{
    tokens = malloc(sizeof(t_token));
    if (!tokens)
    {
        // Handle memory allocation failure
        ft_error_exit("Malloc Error: Token Struct");
    }
    tokens->next = NULL;
    tokens->data = NULL;
    return (tokens);
}

void    init_shell(t_shell **shell)
{   
    (*shell) = malloc(sizeof(t_shell));
    if (!(*shell))
        (*shell)->err_stat = -1;
    else
    {
        (*shell)->err_stat = 0;        //Initial exit status, if there is an error, update err_stat and exit with that code
        (*shell)->tokens = initialize_tokens((*shell)->tokens);
        (*shell)->env_lst = NULL;
    }
}

int main(int ac, char **av, char **envp)
{
    t_shell *shell;
    
    (void)av;
    (void)ac;
    shell = NULL;
    init_shell(&shell);
    (void)envp[0];
    //get_env_var(&(shell->env_lst), envp);     //Store ENV variables
    //avletsnel_sh_lvl(shell.env_lst);          //When the shell is called the ENV variable shell level should increase by 1. NOT YET IMPLEMENTED WIP
    shell_loop(&shell);                         //Main loop where input is read and tokens are generated
    exit(shell->err_stat);
}
