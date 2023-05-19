#include "../minishell.h"

t_tree	*ft_ntree_node(char *content, int type)
{
	t_token	*new;

	new = (t_token *) malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->data = content;	
	new->type = type;
	new->left = NULL;
    new->right = NULL
	return (new);
}
