NAME = ../corewar

FLAGS = -Wall -Werror -Wextra -g

SRCS =	vm_main.c\
	vm_pars_param.c\
	vm_data.c\
	vm_read_champ.c\
	vm_init_map.c\
	vm_fight.c\
	vm_op/vm_live.c\
	vm_op/vm_get_param.c\
	vm_op/vm_add.c\
	vm_op/vm_and.c\
	vm_op/vm_check_param.c\
	vm_op/vm_fork.c\
	vm_op/vm_get_nb_octet.c\
	vm_op/vm_ldi.c\
	vm_op/vm_live.c\
	vm_op/vm_lld.c\
	vm_op/vm_lldi.c\
	vm_op/vm_or.c\
	vm_op/vm_st.c\
	vm_op/vm_sti.c\
	vm_op/vm_sub.c\
	vm_op/vm_xor.c\
	vm_op/vm_zjmp.c

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
