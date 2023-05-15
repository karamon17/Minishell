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
    return (0);
}
