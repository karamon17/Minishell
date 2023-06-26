#include "minishell.h"

char	*prev_node(t_shell *shell, t_token *token)
{
	t_token	*tmp;

	tmp = shell->tokens;
	if (tmp == token)
		return (NULL);
	while (tmp)
	{
		if (tmp->next == token)
			return (tmp->data);
		tmp = tmp->next;
	}
	return (NULL);
}