#include "vm_header.h"

static void	vm_init_proc(t_vm_data *data, t_vm_champ *champ, int pos)
{
    //vm_print_arena();
    //ft_printf("%d, %d\n", pos, champ->header.prog_size);
    if (!data->tab_proc)
    {
        data->tab_proc = (t_vm_proc *)malloc(sizeof(t_vm_proc));
        data->nb_proc = 1;
        memcpy(data->arena + pos, champ->prog, champ->header.prog_size);
    }
    else
    {
        data->tab_proc = (t_vm_proc *)realloc(data->tab_proc, sizeof(t_vm_proc) * (data->nb_proc + 1));
        data->nb_proc++;
        memcpy(data->arena + pos, champ->prog, champ->header.prog_size);
    }
    vm_print_arena();

    data->tab_proc[(data->nb_proc - 1)].beg = 0;
    data->tab_proc[data->nb_proc - 1].carry = 0;
    data->tab_proc[data->nb_proc - 1].champ = champ->num;
    data->tab_proc[data->nb_proc - 1].last_live = 0;
    data->tab_proc[data->nb_proc - 1].pc = 0;
    data->tab_proc[data->nb_proc - 1].registre[1] = champ->num;
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
        //ft_printf("%d, %d\n", i, n);
        vm_init_proc(data, data->tab_champ[i], (i * MEM_SIZE)/n);
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
