/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:55:29 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/21 12:38:07 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	count_quotes(char type, char *str)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		if (type != '\0')
		{
			if (str[i] == type)
				cnt++;
		}
		i++;
	}
	if (cnt % 2 != 0)
	{
		g_error_status = 258;
		ft_putstr_fd("Minishell: syntax error: unexpected end of file\n", 2);
		type = 'E';
	}
	return (type);

}

char	set_quote_type(char *str)
{
	int		i;
	char	fnd;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i] != '\'' && str[i] != '"' && str[i])
		i++;
	if (str[i] == '\'' || str[i] == '"')
	{
		fnd = str[i];
		cnt++;
	}
	i++;
	while (str[i])
	{
		if (str[i] == fnd && fnd != '\0')
			cnt++;
		i++;
	}
	if (cnt % 2 != 0 && cnt != 0)
	{
		g_error_status = 258;
		ft_putstr_fd("Minishell: syntax error: unexpected end of file\n", 2);
		return ('E');
	}
	if (fnd == '\'')
		return ('\'');
	else if (fnd == '"')
		return ('"');
	return ('\0');
}

int	quote_check(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		tmp->type = set_quote_type(tmp->data);
		if (tmp->type != '\0')
		{
			if (!ft_strncmp(&tmp->type, "E", 2))
				return (-1);
		}
		tmp->type = count_quotes(tmp->type, tmp->data);
		tmp = tmp->next;
	}
	return (0);
}
