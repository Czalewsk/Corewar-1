/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 22:48:45 by lduval            #+#    #+#             */
/*   Updated: 2017/05/03 09:10:51 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

void	vm_print_arena(void)
{
	t_vm_data		*dat;
	int				i;

	dat = get_data();
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("\n");
		ft_printf("%.2x", dat->arena[i]);
		//ft_printf("%d: %02x\n", i ,  dat->arena[i]);
		i++;
	}
	ft_putendl("");
}

int		main(int argc, char **argv)
{
	vm_pars_param(argc, argv);
	vm_init_arena();
	vm_fight();
	return (EXIT_SUCCESS);
}
