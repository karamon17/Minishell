/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:45:58 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/26 17:59:17 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*helper(char *result)
{
	free(result);
	return (ft_strdup("$"));
}

char	*ft_get_value(t_shell *shell, char *str, int *k)
{
	char	*result;
	char	*path;
	int		is_env;

	result = ft_calloc(1, sizeof(char));
	path = ft_calloc(1, sizeof(char));
	is_env = 0;
	if (str[*k] == '$' && str[(*k)++])
		is_env = 1;
	while (is_env == 1 && str[*k] && str[*k] != '"' && str[*k] != ' ' && \
		str[*k] != '$' && str[*k] != '\'' && str[*k] != '/' && str[*k] != '=')
		path = ft_mystrjoin2(path, ft_substr(str, (*k)++, 1));
	if (is_env == 1)
	{
		result = ft_mystrjoin2(result, ft_getenv(shell, path));
		if (!path[0])
			result = helper(result);
		if (path[0] == '?')
		{
			result = ft_mystrjoin2(result, ft_itoa(g_error_status));
			result = ft_mystrjoin(result, path + 1);
		}
	}
	free(path);
	return (result);
}
