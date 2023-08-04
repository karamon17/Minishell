# Minishell

Minishell is a simplified version of bash developed as part of the main curriculum 42 school. It provides basic shell functionality, including executing commands, managing environment variables, and handling input/output redirection.

## Features

- Execute commands and display the output.
- Handle basic shell built-in commands.
- Handle environment variable expansion.
- Support input/output redirection (<, >, <<, >>).
- Implement basic signal handling (Ctrl-\, Ctrl-C).
- Implement EOF handling (Ctrl-D).
- Basic error handling and error messages.
- Support for handling multiple commands using pipes.

## Installation

To use Minishell, follow these steps:

1. Clone the repository:

```git clone https://github.com/karamon17/Minishell```

2. Change to the project directory:

```cd Minishell```

3. Compile the source code using `make`:

```make```

4. Run the Minishell executable:

```./minishell```

## Usage

Minishell provides a command-line interface where you can enter commands and execute them. It supports various features and built-in commands similar to bash.

Here are some examples of how to use Minishell:

```shell
$ ls -l              # Execute the "ls" command with the "-l" option
$ echo Hello World   # Print "Hello World" to the console
$ cd /path/to/dir    # Change directory to "/path/to/dir"
$ export VAR=123     # Set the environment variable "VAR" to "123"
```

## Supported Commands

Minishell supports the following built-in commands:

- cd with only a relative or absolute path
- echo with option -n
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no options

Additionally, Minishell can execute external commands by searching for them in the directories listed in the `PATH` environment variable.
