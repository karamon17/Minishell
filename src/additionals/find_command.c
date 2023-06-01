# include "minishell.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void    check_commands(t_shell **shell)
{
    while ((*shell)->tokens)
    {
        if (ft_strcmp((*shell)->tokens->data, "|"))
            //create_pipe();
        else if (ft_strcmp((*shell)->tokens->data, ">>"))
    }
}

// Function to execute a command using execve
void execute_command(char* command) 
{
    char    *args[2];
    args = { command, NULL };
    execve(command, args, NULL);

    // execve only returns if an error occurs
    perror("Error executing command");
    exit(EXIT_FAILURE);
}