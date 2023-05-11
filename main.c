/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:57:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/09 14:57:32 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void    quote_split(t_token **tokens)
{
    int is_quote;
    t_token *tmp;

    tmp = (*tokens);
    while (tmp != NULL)
    {
        if ()
    }
}

t_token **make_tokens(char *input)
{
    t_token **tokens;
    t_token *new;
    int     i;
    char    **tmp;

    i = 0;
    tokens = (t_token **)malloc(sizeof(t_token *));
    tokens = NULL;
    tmp = ft_split(input, ' ');
    while (tmp[i++])
    {
        new = ft_new_token(tmp[i]);
        ft_token_add_back(tokens, new);
    }
    quote_split(tokens);
    return (tokens);
}

int main(int ac, char **av, char **envp)
{
    char    *input;
    t_token **check;     //for testing

    (void)ac;
    (void)av;
    (void)envp; 
    while ((input = readline("Minishell ")) != NULL)
    {
        add_history(input);
        check = make_tokens(input);
        free(input);
    }
    while((*check) != NULL)
    {
        printf("%s\n", (*check)->data);
        (*check) = (*check)->next;
    }
    return (0);
}
