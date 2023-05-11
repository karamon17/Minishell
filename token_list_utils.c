#include "lexer.h"

t_token	*ft_new_token(char *content)
{
	t_token	*new;

	new = (t_token *) malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->data = content;
	new->type = -1;
	new->next = NULL;
	return (new);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2 && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

t_token	*ft_token_last(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			return (tmp);
	}
	return (tmp);
}

void	ft_token_add_back(t_token **stack, t_token *new)
{
	t_token	*n;

	if (*stack)
	{
		n = ft_token_last(*stack);
		n->next = new;
		new->next = NULL;
	}
	else
	{
		*stack = new;
		(*stack)->next = NULL;
	}
}

// int	ft_lstsize(t_list *head)
// {
// 	size_t	i;
// 	t_list	*tmp;

// 	tmp = head;
// 	i = 0;
// 	while (tmp)
// 	{
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	return (i);
// }