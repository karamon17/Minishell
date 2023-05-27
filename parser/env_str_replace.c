// #include "../minishell.h"

// char   *env_in_DQS(char *str)
// {
//     char    *tmp;
//     int     is_env;

//     is_env = 0;
//     tmp = malloc(sizeof(char));
// }

// t_token *env_check(t_token *tokens)
// {
//     t_token *tmp;

//     tmp = tokens;
//     while (tmp)
//     {
//         if (tmp->data[0] == '"')
//             tmp->data = env_in_DQS(tmp->data); //check double quotes for ENV and change to variable PATH
//         else if (tmp->data[0] == '$')
//             tmp->data = get_path(tmp->data);  //ENV is not in quotes, so replace var with ENV PATH
//         tmp = tmp->next;    //to next node
//     }
// }