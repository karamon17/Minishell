/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:59:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/27 13:59:32 by jfrances         ###   ########.fr       */
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

int	ft_exec_error(char *str, char **argv, char **env2darray)
{
	if (!argv && !env2darray)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	else if (!str && !argv && !env2darray)
	{
		ft_putstr_fd("Minishell: fork: Resource temporarily unavailable\n", 2);
		g_error_status = 1;
		return (1);
	}
	else
	{
		ft_free_path(argv);
		ft_free_path(env2darray);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
}
