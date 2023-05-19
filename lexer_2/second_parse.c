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
        //is_option(&head);
        is_redir(&head);
        //is_delimeter(&head);
        is_env(&head);
        if (head->type == -1)
            head->type = ARGUMENT;
        head = head->next;
    }
}

void    gen_ast(t_token **tokens, **tree)
{
    (*tree) = ft_ntree_node((*token)->data);
    (*token) = (*token)->next;
    while ((*token != NULL))
    {
        if ((*token)->type == CMD)
        {
            (*tree)->left = ft_ntree_node((*token)->data, (*token)->type);
            (*tree) = (*tree)->left;
        }
        else if ((*token)->type == PIPE)
        {
            (*tree)->right = ft_ntree_node((*token)->data, (*token)->type);
            (*tree) = (*tree)->right;
        }
    }
}
