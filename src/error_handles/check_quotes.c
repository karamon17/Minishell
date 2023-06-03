#include "minishell.h"

static t_cnt *d_count(char *str, int i, int single)
{
    t_cnt *cnt;

    cnt = malloc(sizeof(t_cnt));
    cnt->singles = single;
    while (str[++i])
    {
        if (str[i] == '"')
            cnt->doubles++;
    }
    cnt->i = i;
    return (cnt);
}

static t_cnt *s_count(char *str, int i, int doubles)
{
    t_cnt *cnt;

    cnt = malloc(sizeof(t_cnt));
    cnt->doubles = doubles;
    while (str[++i])
    {
        if (str[i] == '\'')
            cnt->singles++;
    }
    cnt->i = i;
    return (cnt);
}

int     quote_check(t_token *tokens)
{
    t_cnt   *cnt;
    t_token *tmp;

    cnt = malloc(sizeof(t_cnt));
    cnt->singles = 0;
    cnt->doubles = 0;
    tmp = tokens;
    while (tmp)
    {
        cnt->i = 0;
        while (tmp->data[cnt->i])
        {
            if (tmp->data[cnt->i] == '"')
                cnt = d_count(tmp->data, cnt->i, cnt->singles);
            if (tmp->data[cnt->i] == '\'')  
                cnt = s_count(tmp->data, cnt->i, cnt->doubles);
            printf("cnt == [%d] && i == [%d]\n", cnt->singles, cnt->i);
            if ((cnt->singles % 2 != 0) || (cnt->doubles % 2 != 0))
            {
                free(cnt);
                return (-1);
            }
            cnt->i++;
        }
        tmp = tmp->next;
    }
    return (0);
}