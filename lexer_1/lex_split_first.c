// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   lex_split_first.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/15 16:53:37 by jfrances          #+#    #+#             */
// /*   Updated: 2023/05/22 13:40:01 by gkhaishb         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"
// #include "../lexer.h"

// //after first pass check for pipes

// char *add_white_space(char *input, int j)
// {
//     char *tmp;
//     int tmp_size = 0;

//     while (input[j])
//     {
//         if (input[j] == '|')
//             tmp_size += 2; // Additional space for "|"
//         else if ((input[j] == '<' && input[j + 1] != '<') || (input[j] == '>' && input[j + 1] != '>'))
//             tmp_size += 2; // Additional space for "<" or ">"
//         else if ((input[j] == '<' && input[j - 1] == '<') || (input[j] == '>' && input[j - 1] == '>'))
//             tmp_size += 2; // Additional space for "<<" or ">>"
//         tmp_size++; // Space for the current character
//         j++;
//     }
//     tmp = (char *)malloc((tmp_size + 1) * sizeof(char)); // Allocate memory for the resulting string
//     if (!tmp)
//         // Handle memory allocation error
//         return NULL;
//     tmp[0] = '\0'; // Initialize the string as an empty string
//     j = 0; // Reset the iterator
//     while (input[j])
//     {
//         if (input[j] == '|')
//             tmp = double_strjoin(tmp, input, &j);
//         else if ((input[j] == '<' && input[j + 1] != '<') || (input[j] == '>' && input[j + 1] != '>'))
//             tmp = double_strjoin(tmp, input, &j);
//         else if ((input[j] == '<' && input[j - 1] == '<') || (input[j] == '>' && input[j - 1] == '>'))
//             tmp = double_strjoin(tmp, input, &j);
//         else
//         {
//             tmp = ft_strjoin(tmp, ft_substr(input, j, 1));
//             j++;
//         }
//     }
//     return tmp;
// }

// int d_quotes(char *input, int i, t_token **new)
// {
//     while (input[i] != '"' && input[i] != '\0')
//     {
//        (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
//         i++;
//     }
//     if (input[i] != '\0')
//          (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
//     return (i);
// }

// int append_word(char *input, int i, t_token **new)
// {
//     while (input[i] != ' ' && input[i] != '\0')
//     {
//         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
//         i++;
//     }
//     return (i);
// }

// int s_quotes(char *input, int i, t_token **new)
// {
//     while (input[i] != '\'' && input[i] != '\0')
//     {
//         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
//         i++;
//     }
//     if (input[i] != '\0')
//          (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
//     return (i);
// }

// t_token    *first_parse(char *input, t_token *tokens)
// {
//     int     check = 0;
//     t_token *new;
//     int     i;
//     int     j;
//     char    *tmp;

//     i = 0;
//     j = 0;
//     tmp = add_white_space(input, j);
//     while (tmp[i] == ' ' && tmp[i])
//         i++;
//     while (tmp[i])
//     {
//         new = ft_new_token(ft_substr(tmp, i, 1));
//         if (tmp[i] == '\'')
//             i = s_quotes(tmp, i + 1, &new);
//         else if (tmp[i] == '"')
//             i = d_quotes(input, i + 1, &new);
//         else if (tmp[i] != ' ')
//            i = append_word(tmp, i + 1, &new);
//         if (check == 0)
//             tokens = new;
//         if (check != 0)
//             ft_token_add_back(&tokens, new);
//         i++;
//         check++;
//     }
//     return (tokens);
// }
