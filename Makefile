NAME = minishell

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

HEADER = lexer.h

LIBFT	=	libft/libft.a

FLAGS = -Wall -Wextra -Werror -g -Llibft -lft

all: $(NAME)

%.o: %.c $(HEADER)
	cc $(FLAGS) -c $< -o $@

$(NAME): $(HEADER) $(OBJS) $(LIBFT)
	cc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT)

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
