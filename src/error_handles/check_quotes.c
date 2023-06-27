/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:55:29 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/26 17:48:20 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_move_double_quotes(char **str)
{
	*str = ft_strchr(*str, '"');
	(*str)++;
	*str = ft_strchr(*str, '"');
	if (!(*str))
	{
		g_error_status = 258;
		ft_putstr_fd("Minishell: syntax error: unexpected end of file\n", 2);
		return (1);
	}
	(*str)++;
	return (0);
}

int	ft_move_single_quotes(char **str)
{
	*str = ft_strchr(*str, '\'');
	(*str)++;
	*str = ft_strchr(*str, '\'');
	if (!(*str))
	{
		g_error_status = 258;
		ft_putstr_fd("Minishell: syntax error: unexpected end of file\n", 2);
		return (1);
	}
	(*str)++;
	return (0);
}

int	ft_count_quotes(char *str)
{
	while (str)
	{
		if (ft_strchr(str, '"') && ft_strchr(str, '\''))
		{
			if (ft_strchr(str, '"') < ft_strchr(str, '\'')
				&& ft_move_double_quotes(&str))
				return (1);
			else if (ft_strchr(str, '"') > ft_strchr(str, '\'')
				&& ft_move_double_quotes(&str))
				return (1);
		}
		if (ft_strchr(str, '"') && !ft_strchr(str, '\'')
			&& ft_move_double_quotes(&str))
			return (1);
		else if (!ft_strchr(str, '"') && ft_strchr(str, '\'')
			&& ft_move_single_quotes(&str))
			return (1);
		else if (!ft_strchr(str, '"') && !ft_strchr(str, '\''))
			return (0);
	}
	return (0);
}

int	quote_check(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if ((ft_strchr(tmp->data, '"') || ft_strchr(tmp->data, '\''))
			&& ft_count_quotes(tmp->data))
		{
			tmp->type = 'E';
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
