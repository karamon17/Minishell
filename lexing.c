#include "lexer.h"

//after first pass check for pipes

size_t  ft_strlen(const char *str)
{
    size_t  i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void    d_quotes(char *input, int *i, t_token **new)
{
    int count;

    count = 1;
    while (input[*i] != '"' && input[*i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, &input[*i]);
        i++;
        if (input[*i] == '\'')
            count++;
    }
    printf("dq = %d\n", *i);
}

void    s_quotes(char *input, int *i, t_token **new)
{
    int count;

    count = 0;
    while (input[*i] != '"' && input[*i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, &input[*i]);
        i++;
        if (input[*i] == '"')
            count++;
    }
}

t_token    *first_parse(char *input)
{
    t_token *tokens;
    t_token *new;
    int     i;

    i = -1;
    tokens = malloc(sizeof(t_token));
    tokens = NULL;
    while (input[++i] != ' ' && input[i] != '\0')
    while (input[i] != '\0')
    {
        new = ft_new_token(&input[i]);
        if (input[i] == '\'')
            s_quotes(input, &i, &new);
        else if (input[i] == '"')
            d_quotes(input, &i, &new);
        else if (input[i] != ' ')
            new->data = ft_strjoin(new->data, &input[i]);
        i++;
        ft_token_add_back(&tokens, new);
    }
    return (tokens);
}