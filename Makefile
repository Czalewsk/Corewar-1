NAME = corewar_project

all: $(NAME)

corewar_project:
	make -C asmdir
	make -C vmdir

clean:
	make clean -C asmdir
	make clean -C vmdir

cleanvm:
	make clean -C vmdir
cleanasm:
	make clean -C asmdir

fclean: clean
	rm -f asm
	rm -f corewar

fcleanasm: cleanasm
	rm -f asm

fcleanvm:cleanvm
	rm -f corewar
	
re: fclean
	make
