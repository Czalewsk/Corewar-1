#include "vm_header.h"

static void	vm_init_registre(t_vm_data *data, t_vm_champ *champ, int pos)
{

}

static void vm_init_champ(t_vm_data *data)
{
	int i;
    int n;

	n = 0;
	i = n;
	while (data->tab_champ[n])
		++n;
    ++n;
    while (data->tab_champ[i])
    {
        vm_init_registre(data, data->tab_champ[i], (i * MEM_SIZE)/n);
        i++;
    }
}

void	vm_init_arena()
{
	t_vm_data	*data;
	int			i;

	data = get_data();
	i = 0;
	while (i < MEM_SIZE)
	{
		data->arena[i] = 0;
		i++;
	}
	vm_init_champ(data);
}
