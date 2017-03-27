
ASM = asm
VM = vm

all: $(ASM) $(VM)

$(ASM):
	make -C asmdir
$(VM) :
	make -C vmdir

clean: make fclean -C asm

fclean: clean
	rm -f asm
	rm -f vm

re: fclean
	make
