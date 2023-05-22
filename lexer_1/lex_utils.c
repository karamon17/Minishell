/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:43 by jfrances          #+#    #+#             */
/*   Updated: 2023/05/22 13:50:34 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../lexer.h"

char	*double_strjoin(char *tmp, char *input, int *j)
{
	tmp = ft_strjoin(tmp, ft_substr(input, *j, 1));
    tmp = ft_strjoin(tmp, " ");
	(*j)++;
	return (tmp);
}
