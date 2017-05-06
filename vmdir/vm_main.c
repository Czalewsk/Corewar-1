/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 22:48:45 by lduval            #+#    #+#             */
/*   Updated: 2017/05/06 04:01:20 by lduval           ###   ########.fr       */
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
	int		n;

	dat = get_data();
	tmp = (dat->tab_proc);
	ft_putendl("");
	while (tmp)
	{
		n = -1;
		tproc = tmp->content;
		ft_printf("PC={red}%i{eoc}\n", tproc->pc);
		while (++n < 16)
			ft_printf("REG[%i]=%i\n", n, ((int*)tproc->registre)[n]);
		ft_putendl("");
		tmp = tmp->next;
	}
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
}	

int		main(int argc, char **argv)
{
	vm_pars_param(argc, argv);
	vm_init_arena();
	vm_fight();
	return (EXIT_SUCCESS);
}
