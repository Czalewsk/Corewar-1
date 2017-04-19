#include "vm_header.h"

static void	vm_init_registre()
{
	return;
}

static void vm_init_champ(t_vm_data *data)
{
	int i
	
	i = 0;
	while (data.tab_champ[i])
		i++;
	
}

void	vm_init_arena()
{
	t_vm_data	*data;
	int			i;

	data = get_data();
	i = 0;
	while (i < MEM_SIZE)
	{
		data.arena[i] = 0;
		i++;
	}
	vm_init_champ();
}
