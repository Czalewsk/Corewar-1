/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 22:48:45 by lduval            #+#    #+#             */
/*   Updated: 2017/05/05 17:51:59 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

void	vm_print_arena(void)
{
	t_vm_data		*dat;
	int				i;
	static int		j = 0;
	char *l;
	t_list	*tmp;
	t_vm_proc *tproc;

	dat = get_data();
	i = 0;
	if (!j)
	{
		while (i < MEM_SIZE)
		{
			if (i % 64 == 0)
				ft_printf("\n");
			if (dat->col_arena[i] != 0)
				ft_printf("\033[%dm", 90 + dat->col_arena[i]);
			ft_printf("%.2x ", dat->arena[i]);
			if (dat->col_arena[i] != 0)
				ft_printf("\033[0m");
			//ft_printf("%d: %02x\n", i ,  dat->arena[i]);
			i++;
		}
		ft_putendl("");
		j = get_next_line(0, &l);
		j = (j > -1) ? ft_atoi(l) : 0;
		j = j < 0 ? -j : j;
		free(l);
	}
	else
		j--;
	tmp = (dat->tab_proc);
	while (tmp)
	{
		tproc = 
		tmp = tmp->next;
	}
}	

int		main(int argc, char **argv)
{
	vm_pars_param(argc, argv);
	vm_init_arena();
	vm_fight();
	return (EXIT_SUCCESS);
}
