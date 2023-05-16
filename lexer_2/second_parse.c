/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:54:58 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/16 14:15:46 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void    second_parse(t_token **tokens)
{
    t_token *head;
    head = (*tokens);
    while(head != NULL)
    {
        is_b_in(&head);
        is_pipe(&head);
        is_option(&head);
        is_redir(&head);
        //is_delimeter(&head);
        is_env(&head);
        if (head->type == -1)
            head->type = TEXT;
        head = head->next;
    }
}
