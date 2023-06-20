/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <gkhaishb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:57:30 by jfrances          #+#    #+#             */
/*   Updated: 2023/06/20 18:52:17 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RED_COLOR   "\x1B[31m"
#define GRN_COLOR "\x1B[32m"
#define RESET_COLOR "\x1B[0m"

static int	error_in_tokens(t_shell **shell)
{
	t_token	*tmp;

	tmp = (*shell)->tokens;
	while (tmp)
	{
		if (tmp->type != '\0')
		{
			if (tmp->type == 'E')
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

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
	printf(RED_COLOR "----------------------------------------\n" RESET_COLOR);
}

int	shell_loop(t_shell **shell)
{
	t_token		*head_tokens;
	t_constr	*head_constr;
	char		*input;

	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("Minishell $>");
		(*shell)->constrs = NULL;
		(*shell)->tokens = NULL;
		if (!input)
			return (printf("\x1b[1A\x1b[13Cexit\n"));
		if (input[0])
		{
			add_history(input);
			head_tokens = first_parse(input, (*shell), 0);
			kani_heredoc(shell);
			if (error_in_tokens(shell) == -1)
				continue ;
			env_check(*shell, head_tokens);
			(*shell)->tokens = stugel(head_tokens);
			g_error_status = 0;
			head_constr = create_constr(*shell);
			kani_heredoc(shell);
			if ((*shell)->constrs)
				ft_pipex(*shell);
			free_constrs(head_constr);
			//system("leaks minishell");
		}
		else
			free(input);
	}
}

void	init_shell(t_shell **shell)
{
	g_error_status = 0;
	(*shell) = malloc(sizeof(t_shell));
	(*shell)->tokens = NULL;
	(*shell)->constrs = NULL;
	(*shell)->env_lst = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)av;
	(void)ac;
	shell = NULL;
	print_cool_head();
	init_shell(&shell);
	add_shlvl(envp);
	get_env_var(&(shell->env_lst), envp);
	shell_loop(&shell);
	free_env_list(shell);
	//system("leaks minishell");
	exit(g_error_status);
}
