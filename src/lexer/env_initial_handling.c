/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initial_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:00:11 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/27 14:01:41 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*ft_add_new_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	free(key);
	free(value);
	return (node);
}

t_env	*ft_add_env_back(t_env *env_list, char *key, char *value)
{
	t_env	*node;
	t_env	*clone;

	if (!key)
		return (NULL);
	node = ft_add_new_env(key, value);
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
		j++;
		if (envp[i][j] && ft_strncmp(key, "OLDPWD", 7))
			value = ft_substr(envp[i], j, ft_strlen(envp[i]) - j);
		else
			value = NULL;
		*env_lst = ft_add_env_back(*env_lst, key, value);
		i++;
	}
}
