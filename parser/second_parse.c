/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:38:27 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/27 19:38:29 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

// == ft_strlen(tmp->data)

void delete_token(t_token **head, t_token *to_delete) 
{
    t_token *prevNode;

    if (*head == NULL || to_delete == NULL)
        return;
    if (*head == to_delete) 
    {
        printf("in delete function?");
        (*head)->next = to_delete->next;
        free(to_delete);
        return;
    }
    prevNode = *head;
    while (prevNode->next != NULL && prevNode->next != to_delete)
        prevNode = prevNode->next; 
    if (prevNode->next == NULL)
        return;
    prevNode->next = to_delete->next;
    free(to_delete);
}

t_token *check_options(t_token *tokens) 
{
    t_token *tmp;
    t_token *to_delete;
    int foundN;

    tmp = tokens;
    foundN = 0;
    while (tmp != NULL) 
    {
        if (ft_strcmp(tmp->data, "-n") == 0)
            foundN = 1;
        else if (foundN) 
        {
            if (tmp->data[0] == '-' && ft_strlen(tmp->data) > 1 && strspn(tmp->data, "-")) 
            {
                to_delete = tmp;
                tmp = tmp->next;
                delete_token(&tokens, to_delete);
                continue ;
            }
        }
        tmp = tmp->next;
    }
    return (tokens);
}

t_token *stugel(t_token *tokens) 
{
    t_token *tmp;
    int i;

    tmp = tokens;
    i = 0;
    while (tmp != NULL) 
    {
        if (ft_strncmp(tmp->data, "echo", 5) == 0 && i == 0)
        {
            printf("check is good\n");
            tokens = check_options(tmp);
        }
        tmp = tmp->next;
        i++;
    }
    return tokens;
}
