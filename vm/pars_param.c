static void vm_pars_champions(int nb_param, char **tab_param, int *count)
{
	int i;
	unsigned int n_next_player;
	unsigned int n_free;
	int finsh;


	i = *count;
	n_free = 0;
	while (i < nb_param && !fish)
	{
		if (ft_strequ("-n", tab_parm[i]))
		{
			
		}
		else
			n_next_player = n_free;
		if (ft_
	}
	*count = i;

}

static void vm_pars_option(int nb_param, char **tab_param, int i)
{
	while (i < nb_param)
	{

	}

}

static void vm_pars_dump(char **tab_param, t_vm)
{
	int dump;

	dump = 0;
	if (ft_strequ(tab_param[0], "-dump"))
		ft_error("first parametre must be '-dump'", &vm_free_all);
	if (!ft_isnumber(tab_param[1]))
		ft_error("second parametre must be a number", &vm_free_all);
	if (dump = ft_atoi(tab_param[1]) <= 0)
		ft_error("second parametre must be positive", &vm_free_all);
	return (0);
}

/*
** [pars_param()]
** Verifie si la machine est lancée de la bonne manière
** soit de la manière suivante 
** ./corewar [-dump nbr_cycles] [[-n number] champion.cor] ...[-g]
*/

int	vm_pars_param(int nb_parm, char **tab_parm)
{
	int error;
	int i;

	error = 0;
	i = 3;
	dump = 0;
	if (nb_para < 4)
		ft_error("not enought parametre", &free_all);
	vm_pars_dump(tab_param);
	vm_pars_champions(nb_param, tab_param, &i);
	vm_pars_option(nb_param, tab_param, i);
	return (error)
}
