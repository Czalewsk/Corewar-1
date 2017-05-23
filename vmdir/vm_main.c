/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 22:48:45 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 11:57:28 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

void	vm_print_arena(void)
{
	t_vm_data		*dat;
	int				i;

	dat = get_data();
	ft_putendl("");
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0)
			ft_printf("\n");
		if (dat->col_arena[i] != 0)
			ft_printf("\033[%dm", 90 + dat->col_arena[i]);
		ft_printf("%.2x ", dat->arena[i]);
		if (dat->col_arena[i] != 0)
			ft_printf("\033[0m");
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
