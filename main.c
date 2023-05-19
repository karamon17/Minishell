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

void    shell_loop(t_token **tokens)
{
    t_tree      *ast;
    t_token     *check;
    char        *input;

    while ((input = readline("Minishell $>")) != NULL)
    {
        add_history(input);
        if (ft_strcmp(input, "exit") == 0)
            break ;
        check = first_parse(input, *tokens);
        // while (check != NULL)
        // {
        //     printf("[%s]\n", check->data);
        //     check = check->next;
        // }
        ast = buildAST(&check);
        printAST(ast);
        free(input);
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

int main(int ac, char **av)
{
    t_token *tokens;
    
    (void)av;
    tokens = NULL;
    if (ac > 1)
         exit (1);
    tokens = initalize_tokens(&tokens);
    shell_loop(&tokens);
    return (0);
}
