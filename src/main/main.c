/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:57:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/14 16:50:51 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cool_head(void)
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

void	shell_loop(t_shell **shell)
{
	char	*input;

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
				exit((*shell)->err_stat);
			add_history(input);
			(*shell)->tokens = first_parse(input, (*shell), 0);
			(*shell)->tokens = env_check(*shell, (*shell)->tokens);
			(*shell)->tokens = stugel((*shell)->tokens);
			kani_heredoc(shell);
			create_constr(*shell);
			ft_pipex(*shell);            
		}
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

    (void)av;
    (void)ac;
    shell = NULL;
    print_cool_head();
    init_shell(&shell);
    (void)envp[0];
    get_env_var(&(shell->env_lst), envp);
    aveletsnel_shvl(shell->env_lst); //WIP
    shell_loop(&shell);
    exit(shell->err_stat);
}
