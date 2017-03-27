

ASM = asm
VM = vm

all: $(ASM) $(VM)

$(ASM):
	make -C asmdir
$(VM) :
	make -C vmdir

clean:
	make clean -C asmdir
	make clean -C vmdir

cleanvm:
	make clean -C vmdir
cleanasm:
	make clean -C asmdir

fclean: clean
	rm -rf asm
	rm -f corewar

fcleanasm: cleanasm
	rm -rf asm

fcleanvm:cleanvm
	rm -rf corewar
	
re: fclean
	make
