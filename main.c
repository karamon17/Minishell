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

// static void make_tokens(char *input)
// {
//     t_token *tokens;
//     t_token *new;
//     int     i;
//     char    **tmp;

//     i = -1;
//     tokens = malloc(sizeof(t_token));
//     tokens = NULL;
//     tmp = ft_split(input, ' ');
//     while (tmp[++i] != NULL)
//     {
//         new = ft_new_token(tmp[i]);
//         ft_token_add_back(&tokens, new);
//     }
// }

int main(int ac, char **av, char **envp)
{
    char    *input;
    t_token    *check;

    (void)ac;
    (void)av;
    (void)envp;
    while ((input = readline("Minishell $")) != NULL)
    {
        add_history(input);
        if (ft_strcmp(input, "exit") == 0)
            break ;
        check = first_parse(input);
        free(input);
    }
    // while (check != NULL)
    // {
    //     printf("%s\n", check->data);
    //     check = check->next;
    // }
    return (0);
}
