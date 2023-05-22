#include "lexer.h"
#include "minishell.h"

//after first pass check for pipes

int   d_quotes(char *input, int i, t_token **new)
{
    while (input[i] != '"' && input[i] != '\0')
    {
       (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    if (input[i] != '\0')
         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
    return (i);
}

int    append_word(char *input, int i, t_token **new)
{
    while (input[i] != ' ' && input[i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    return (i);
}

int    s_quotes(char *input, int i, t_token **new)
{
    while (input[i] != '\'' && input[i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    if (input[i] != '\0')
         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
    return (i);
}

// t_token    *first_parse(char *input)
// {
//     t_token *tokens;
//     t_token *new;
//     int     i;

//     i = 0;
//     tokens = malloc(sizeof(t_token));
//     tokens = NULL;
//     while (input[i] == ' ' && input[i] != '\0')
//         i++;
//     while (input[i])
//     {
//         new = ft_new_token(ft_substr(input, i, 1));
//         if (input[i] == '\'')
//             i = s_quotes(input, i + 1, &new);
//         else if (input[i] == '"')
//             i = d_quotes(input, i + 1, &new);
//         else if (input[i] != ' ')
//            i = append_word(input, i + 1, &new);
//         ft_token_add_back(&tokens, new);
//         i++;
//     }
//     while(tokens != NULL)
//     {
//         printf("%s\n", tokens->data);
//         tokens = tokens->next;
//     }
//     return (tokens);
// }
