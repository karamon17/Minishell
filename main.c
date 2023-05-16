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
    exit(1);
}

void    shell_loop(t_token *tokens)
{
    t_token     *check;
    char        *input;

    while ((input = readline("Minishell $>")) != NULL)
    {
        add_history(input);
        if (ft_strcmp(input, "exit") == 0)
            break ;
        check = first_parse(input, tokens);
        free(input);
    }
}

t_shell    *initalize_shell(t_shell *shell)
{
    shell = malloc(sizeof(t_shell));
    if (!shell)
        ft_error_exit("Malloc Error: Shell Struct");
    shell->tokens = malloc(sizeof(t_token));
    if (!shell->tokens)
    {
        free(shell);
        ft_error_exit("Malloc Error: Tokens Struct");
    }
    shell->cmd_tree = malloc(sizeof(t_tree));
    if (!shell->cmd_tree)
    {
        free(shell->tokens);
        free(shell);
        ft_error_exit("Malloc Error: ABCT Struct");
    }
    shell->tokens = NULL;
    shell->cmd_tree = NULL;
    return (shell);
}

int main(int ac, char **av)
{
    t_shell     *shell;
    
    (void)ac;
    (void)av;
    shell = NULL;
    if (ac > 1)
         exit (1);
    shell = initalize_shell(shell);
    shell_loop(shell->tokens);
    return (0);
}
