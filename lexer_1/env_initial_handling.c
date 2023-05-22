#include "../lexer.h"

void    printENV(t_env *env_lst)
{
    t_env   *tmp;

    tmp = env_lst;
    while (tmp != NULL)
    {
        printf("[Key == %s, value == %s, flag == %d]\n", env_lst->key, env_lst->value, env_lst->flag);
        tmp = tmp->next;
    }
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		len;

	len = ft_strlen(s1);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	while (*s1)
		ptr[i++] = *s1++;
	ptr[i] = '\0';
	return (ptr);
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

void    get_env_var(t_env **env_lst, char **envp)
{
    int		i;
	int		j;
	char	*key;
	char	*value;

	// key = NULL;
	// value = NULL;
	i = 0;
	*env_lst = NULL;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		key = ft_substr(envp[i], 0, j);
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