#include "vm_header.h"

static void	vm_init_registre()
{
	return;
}

static void vm_init_champ()
{
	return;
}

void	vm_init_arena()
{
	t_vm_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (i < MEM_SIZE)
	{
		vm_init_registre();
		i++;
	}
	vm_init_champ();
}
