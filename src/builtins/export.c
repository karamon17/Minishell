/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:31:45 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/06/27 15:26:47 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_add(t_shell *shell, char *key, char *value, int *cat)
{
	t_env	*env;

	env = shell->env_lst;
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			break ;
		env = env->next;
	}
	if (!env)
		ft_add_env_back(shell->env_lst, key, value);
	else if (*cat == 0)
	{
		free(env->value);
		env->value = ft_strdup(value);
		free(value);
	}
	else
		env->value = ft_mystrjoin2(env->value, value);
}

void	ft_print_export(t_shell *shell, char **tmp)
{
	t_env	*current;

	if (!tmp[1])
	{
		current = shell->env_lst;
		while (current)
		{
			printf("declare -x ");
			printf("%s", current->key);
			if (current->value)
				printf("=\"%s\"", current->value);
			printf("\n");
			current = current->next;
		}
	}
}

int	ft_checkletter(char *arg, int *cat)
{
	int	res;

	if (!arg[0])
		return (0);
	res = ((arg[0] >= 'a' && arg[0] <= 'z') || \
		(arg[0] >= 'A' && arg[0] <= 'Z') || arg[0] == '_');
	if (!res)
		return (0);
	res = !ft_strchr(arg, '-') && !ft_strchr(arg, '{')
		&& !ft_strchr(arg, '}') && !ft_strchr(arg, '$')
		&& !ft_strchr(arg, '#') && !ft_strchr(arg, '*')
		&& !ft_strchr(arg, '.') && !ft_strchr(arg, '@')
		&& !ft_strchr(arg, '=') && !ft_strchr(arg, '^');
	if (ft_strchr(arg, '+') && ft_strchr(arg, '+') != &arg[ft_strlen(arg) - 1])
		res = 0;
	else if (ft_strchr(arg, '+') == &arg[ft_strlen(arg) - 1])
	{
		*cat = 1;
		arg[ft_strlen(arg) - 1] = 0;
	}
	return (res);
}

void	ft_printerror(char *tmp, char *value)
{
	g_error_status = 1;
	if (value)
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("=", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	free(value);
}

void	ft_export(t_shell *shell, int *flag, t_const *example)
{
	char	*value;
	char	**tmp;
	int		i;
	int		cat[1];

	*flag = 1;
	*cat = 0;
	tmp = ft_split(shell->constrs->data, ' ');
	i = 0;
	ft_print_export(shell, tmp);
	shell->fd = file_check(example, shell->fd, &shell->flag);
	while (tmp[++i])
	{
		if (!ft_strchr(tmp[i], '='))
			value = NULL;
		else
		{
			value = ft_strdup(ft_strchr(tmp[i], '=') + 1);
			*(ft_strchr(tmp[i], '=')) = 0;
		}
		export_helper(tmp[i], shell, value, cat);
	}
	ft_free_path(tmp);
	close_file(shell->fd);
}
