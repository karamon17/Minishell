#include "minishell.h"

void    free_tokens(t_shell **shell)
{
    t_tokens    *tmp;

    while (tmp != NULL)
    {
        tmp = (*shell)->tokens;
        (*shell)->tokens = (*shell)->tokens->next;
        free(tmp);
    }
}

void    free_env_list(t_shell **shell)
{
    t_env *tmp;

    while (tmp != NULL)
    {
        tmp = (*shell)->env_lst;
        (*shell)->env_lst = (*shell)->env_lst->next;
        free(tmp);
    }
}

void    free_shell(t_shell **shell)
{
    free_tokens(shell);
    free_env(shell);
    free(shell);
}