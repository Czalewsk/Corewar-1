NAME = ../asm

FLAGS = -Wall -Werror -Wextra -g

SRCS =	main.c write_bin.c debug.c get_lex.c set_lex.c \
		delete_lex.c op.c check1.c parse.c check_name_and_cmt.c

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