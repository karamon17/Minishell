#include "lexer.h"

//after first pass check for pipes

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	cnt;

	cnt = 0;
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)malloc ((sizeof(char) * (len + 1)));
	if (!sub)
		return (0);
	while (cnt < len)
	{
		sub[cnt] = s[start + cnt];
		cnt++;
	}
	sub[cnt] = '\0';
	return (sub);
}

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

int   d_quotes(char *input, int i, t_token **new)
{
    while (input[i] != '"' && input[i] != '\0')
    {
       (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    if (input[i] != '\0')
         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
    return (i);
}

int    append_word(char *input, int i, t_token **new)
{
    while (input[i] != ' ' && input[i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    return (i);
}

int    s_quotes(char *input, int i, t_token **new)
{
    while (input[i] != '\'' && input[i] != '\0')
    {
        (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
        i++;
    }
    if (input[i] != '\0')
         (*new)->data = ft_strjoin((*new)->data, ft_substr(input, i, 1));
    return (i);
}

t_token    *first_parse(char *input)
{
    t_token *tokens;
    t_token *new;
    int     i;

    i = 0;
    tokens = malloc(sizeof(t_token));
    tokens = NULL;
    while (input[i] == ' ' && input[i] != '\0')
        i++;
    while (input[i])
    {
        new = ft_new_token(ft_substr(input, i, 1));
        if (input[i] == '\'')
            i = s_quotes(input, i + 1, &new);
        else if (input[i] == '"')
            i = d_quotes(input, i + 1, &new);
        else if (input[i] != ' ')
           i = append_word(input, i + 1, &new);
        ft_token_add_back(&tokens, new);
        i++;
    }
    while(tokens != NULL)
    {
        printf("%s\n", tokens->data);
        tokens = tokens->next;
    }
    return (tokens);
}
