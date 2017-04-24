NAME = ../asm

FLAGS = -Wall -Werror -Wextra -g

SRCS =	main.c write_bin.c debug.c get_lex.c set_lex.c \
		delete_lex.c op.c parse.c write_player.c	   \
		check_function.c get_function1.c			   \
		get_function2.c is_function.c prepare_to_buff.c\
		error_manager.c label.c tab_error.c read_champ.c \
		write_player_reverse.c

INCLUDES = -I includes -I ../libft

DEP = Makefile includes/

LIB = -L ../libft

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): mylibft $(OBJS)
	gcc $(LIB) $(FLAGS) $(OBJS) -o $(NAME) -lft

mylibft:
	make -C ../libft/

%.o: srcs/%.c $(DEP)
	gcc $(FLAGS) $(INCLUDES) -c $<

clean:
	rm -f $(OBJS)
	make -C ../libft/ fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.NOTPARELLEL: all clean fclean re
