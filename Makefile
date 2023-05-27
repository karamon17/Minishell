NAME = minishell

SRCS = $(wildcard *.c) $(wildcard execute/*.c) $(wildcard lexer/*.c) $(wildcard parser/*.c) ##$(wildcard utils/*.c) $(wildcard builtins/*.c)

OBJS = $(SRCS:.c=.o)

HEADER = minishell.h

LIBFT	=	libft/libft.a

FLAGS = -Wall -Wextra -Werror -g 

all: $(NAME)

%.o: %.c $(HEADER)
	cc $(FLAGS) -c $< -o $@

$(NAME): $(HEADER) $(OBJS) $(LIBFT)
	cc $(FLAGS) $(OBJS) -Llibft -lft -lreadline -o $(NAME) 

$(LIBFT) : 
		make -C ./libft

clean:
	rm -f $(OBJS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY:	all clean fclean re
