
static void	vm_init_registre();
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
	if (!(data->arena = (t_reg *)malloc(sizeof(t_reg) * MEM_SIZE)))
		ft_error("malloc arena failed in vm_int_arena", &vm_free_all);
	while (i < MEM_SIZE)
	{
		vm_init_registre();
		i++;
	}
	vm_init_champ();
}
