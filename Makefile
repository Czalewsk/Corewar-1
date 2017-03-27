
ASM = asm
VM = vm

all: $(ASM) $(VM)

$(ASM):
	make -C asm
$(VM) :
	make -C vm

clean: make fclean -C asm

fclean: clean
	rm -f asm
	rm -f vm

re: fclean
	make
