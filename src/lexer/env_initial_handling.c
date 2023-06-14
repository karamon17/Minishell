/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initial_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:37:42 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 17:06:25 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aveletsnel_shvl(t_env *env_lst)
{
	char	*val;
	char	*tmp;
	int		lvl;

	val = find_env_val(env_lst, "SHLVL");
	if (!val)
		return ;
	lvl = ft_atoi(val + 1);
	free(val);
	while (env_lst && env_lst->next)
	{
		if (ft_strcmp("SHLVL", env_lst->key) == 0)
		{
			tmp = ft_itoa(lvl);
			env_lst->value = tmp;
			return ;
		}
		env_lst = env_lst->next;
	}
}

char	*find_env_val(t_env *env_lst, char *key)
{
	t_env	*head;

	if (!key || key[0] == '$')
		return (NULL);
	head = env_lst;
	while (head && ft_strcmp(head->key, key))
		head = head->next;
	if (!head)
		return (NULL);
	return (head->value);
}

t_env	*ft_add_new_env(char *key, char *value, int flag)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->flag = flag;
	node->next = NULL;
	return (node);
}

t_env	*ft_add_env_back(t_env *env_list, char *key, char *value, int flag)
{
	t_env	*node;
	t_env	*clone;

	if (!key)
		return (NULL);
	node = ft_add_new_env(key, value, flag);
	if (!node)
		exit(1);
	clone = env_list;
	if (env_list == NULL)
		return (node);
	while (clone->next != NULL)
		clone = clone->next;
	clone->next = node;
	return (env_list);
}

void	get_env_var(t_env **env_lst, char **envp)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	*env_lst = NULL;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		key = ft_substr(envp[i], 0, j);
		if (!ft_strncmp(key, "OLDPWD", 7))
		{
			i++;
			continue ;
		}
		j++;
		if (envp[i][j])
			value = ft_substr(envp[i], j, ft_strlen(envp[i]) - j);
		*env_lst = ft_add_env_back(*env_lst, key, value, ENV);
		free(key);
		free(value);
		key = NULL;
		value = NULL;
		i++;
	}
}
