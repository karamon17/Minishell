/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:57:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/09 14:57:09 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

#define RED_COLOR   "\x1B[31m"
#define GRN_COLOR "\x1B[32m"
#define RESET_COLOR "\x1B[0m"

void    print_cool_head(void)
{
    printf(RED_COLOR "----------------------------------------\n" RESET_COLOR);
    printf(RED_COLOR "|         WELCOME TO THE SHELL         |\n" RESET_COLOR);
    printf(RED_COLOR "|             THE MINISHELL            |\n" RESET_COLOR);
    printf(RED_COLOR "----------------------------------------\n" RESET_COLOR);
    printf(GRN_COLOR "     -----------------------------      \n" RESET_COLOR);
    printf(GRN_COLOR "     |                           |      \n" RESET_COLOR);
    printf(GRN_COLOR "     |   How May Shell Assist?   |      \n" RESET_COLOR);
    printf(GRN_COLOR "     |                           |      \n" RESET_COLOR);
    printf(GRN_COLOR "     -----------------------------      \n" RESET_COLOR);
    printf(RED_COLOR "----------------------------------------\n" GRN_COLOR);
}

void    ft_error_exit(char *str)
{
    while (*str)
        write(2, str++, 1);
}

void    shell_loop(t_shell **shell)
{
    t_token     *new;
    char        *input;

    (*shell)->err_stat = 0;
	rl_catch_signals = 0;
    while (1)
    {
        signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
        input = readline("Minishell $>");
        if (!input || (*shell)->err_stat != 0)
		{	
			printf("\x1b[1A\x1b[13Cexit\n");
			return ;
		}
		if (input[0])
        {
            if ((*shell)->err_stat != 0)
                exit((*shell)->err_stat); //implement a function to free data later
            add_history(input);
            new = first_parse(input, (*shell)->tokens, (*shell));
            new = stugel(new);
            (*shell)->tokens = new;
            new = env_check(*shell, new);
            //check_commands(shell);
			create_constr(*shell);
			ft_pipex(*shell);
        }
		free(input);
    }
}

t_token *initialize_tokens(t_token *tokens)
{
    tokens = malloc(sizeof(t_token));
    if (!tokens)
        ft_error_exit("Malloc Error: Token Struct");
    tokens->next = NULL;
    tokens->data = NULL;
    return (tokens);
}

t_constr *initialize_constr(t_constr *constrs)
{
    constrs = malloc(sizeof(t_token));
    if (!constrs)
        ft_error_exit("Malloc Error: Constrs Struct");
    constrs->next = NULL;
	constrs->prev = NULL;
    constrs->data = NULL;
	constrs->command = NULL;
    return (constrs);
}

void    init_shell(t_shell **shell)
{   
    (*shell) = malloc(sizeof(t_shell));
    if (!(*shell))
        (*shell)->err_stat = -1;
    else
    {
        (*shell)->err_stat = 0;        //Initial exit status, if there is an error, update err_stat and exit with that code
        (*shell)->tokens = initialize_tokens((*shell)->tokens);
		(*shell)->constrs = initialize_constr((*shell)->constrs);
        (*shell)->env_lst = NULL;
    }
}

int main(int ac, char **av, char **envp)
{
    t_shell *shell;

    (void)av;
    (void)ac;
    shell = NULL;
    print_cool_head();
    init_shell(&shell);
    (void)envp[0];
    get_env_var(&(shell->env_lst), envp);     //Store ENV variables in ENV linked list
    aveletsnel_shvl(shell->env_lst);          //When the shell is called the ENV variable shell level should increase by 1. NOT YET IMPLEMENTED WIP
    shell_loop(&shell); //Main loop where input is read and tokens are generated
    exit(shell->err_stat);
}
