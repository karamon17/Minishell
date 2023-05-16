/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_assignment_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:15:54 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/16 14:16:01 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void    is_b_in(t_token **head)
{
    if (ft_strcmp((*head)->data, "echo") == 0)
        (*head)->type = B_IN;
    else if (ft_strcmp((*head)->data, "cd") == 0)
         (*head)->type = B_IN;
    else if (ft_strcmp((*head)->data, "pwd") == 0)
         (*head)->type = B_IN;
    else if (ft_strcmp((*head)->data, "export") == 0)
         (*head)->type = B_IN;
    else if (ft_strcmp((*head)->data, "unset") == 0)
         (*head)->type = B_IN;
    else if (ft_strcmp((*head)->data, "env") == 0)
         (*head)->type = B_IN;
    else if (ft_strcmp((*head)->data, "exit") == 0)
         (*head)->type = B_IN;
}

void    is_pipe(t_token **head)
{
    int i;

    i = 0;
    while ((*head)->data[i])
    {
        if ((*head)->data[i] == '|')
        {
            (*head)->type = PIPE;
            break ;
        }
        i++;
    }
}

void    is_env(t_token **head)
{
    if (getenv((*head)->data) != NULL)
        (*head)->type = ENV;
}





// void    is_r_dir(t_token **head)                //Function will require subfunctions and a count of redirects
// {                                               //Maybe split redirects into additional nodes for the ACBT(?)
//     int i;

//     i = 0;
//     while ((*head)->data[i] != '\0')
//     {
//         if ((*head)->data[i] == '>' && (*head)->data[i + 1] == '>')
//         {
//             (*head)->type = PIPE;
//             break ;
//         }
//         i++;
//     }
// }

// void    is_delimiter(t_token **head)                //Function will require subfunctions and a count of delimeters i.e. "<<a>>b<<c"
// {                                                   //Maybe split delimeters into additional nodes for the ACBT(?)
//     int i;

//     i = 0;
//     while ((*head)->data[i] != '\0')
//     {
//         if ((*head)->data[i] == '>' && (*head)->data[i + 1] == '>')
//         {
//             (*head)->type = PIPE;
//             break ;
//         }
//         i++;
//     }
// }

//NOTE: POSSIBLE SOLUTION IS TO LOOP THROUGH LINKED LIST AND STORE INTO A SECOND LINKED LIST (OUR ABSTRACT COMMAND BINARY TREE)
//AFTER FREE FIRST LINKED LIST SEND NEW LIST TO EXECUTION PHASE. 
