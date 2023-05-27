# include "../minishell.h"
                                                    
t_token *check_options(t_token *tmp)
{
    t_token *tmp2;
    t_token *tmp3;

    tmp2 = tmp;
    tmp2 = tmp2->next;
    while (tmp2)
    {
        if (ft_strcmp(tmp->data, "-n"))
        {
            tmp3 = tmp2;
            tmp2 = tmp2->next;
            while (ft_strcmp(tmp->data, "-n"))
            {   
                tmp3->next = tmp2->next;
                free(tmp2);
                tmp2 = tmp3->next;
            }
        }
    }
    return (tmp);
}

t_token *stugel(t_token *tokens)
{
    t_token *tmp;
    int     i;

    tmp = tokens;
    i = 0;
    while (tmp)
    {
        if (ft_strncmp(tmp->data, "echo", 4) && i == 0)
            tokens = check_options(tmp);
        //else if (tmp->data[i] == '"')
            //d_quote_env_chk(tmp);
        tmp = tmp->next;
        i++;
    }
    return (tokens);
}