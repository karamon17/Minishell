/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:38:27 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/13 15:32:27 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_token    *cut_command_quotes(t_token *tokens)
{
    int         i;
    char        *cpy;
	char        *tmp_str;
    t_token     *tmp;
    char        c;

    tmp = tokens;
    while (tmp != NULL)
    {   
        c = tmp->data[0];
        i = -1;
        cpy = ft_calloc(1, sizeof(char));
        while (tmp->data[++i])
        {
            if (tmp->data[i] == '\'' && tmp->data[i] == c)
                continue ;
            if (tmp->data[i] == '"' && tmp->data[i] == c)
                continue ;
			tmp_str = cpy;
            cpy = ft_strjoin(cpy, ft_substr(tmp->data, i, 1));
			free(tmp_str);
        }
        tmp->data = ft_strdup(cpy);
        tmp = tmp->next;
    }
    free(cpy);
    return (tokens);
}

void delete_token(t_token **head, t_token *to_delete) 
{
    t_token *prevNode;

    if (*head == NULL || to_delete == NULL)
        return;
    if (*head == to_delete) 
    {
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
	char *temp_str;

    tmp = tokens->next;
	if (tmp->data[0] == '-' && !ft_strncmp(ft_strtrim(tmp->data, "n"), "-", 2))
	{
		temp_str = tmp->data;
		tmp->data = ft_strdup("-n");
		free(temp_str);
		tmp = tmp->next;
	}
	else
		return (tokens);
    while (tmp != NULL) 
    {
		if (tmp->data[0] == '-' && !ft_strncmp(ft_strtrim(tmp->data, "n"), "-", 2))
		{
			to_delete = tmp;
			tmp = tmp->next;
			delete_token(&tokens, to_delete);
			continue ;
		}
		return (tokens);
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
            tokens = check_options(tmp);
        tmp = tmp->next;
        i++;
    }
    tmp = tokens;
    tokens = cut_command_quotes(tmp);
    return (tokens);
}