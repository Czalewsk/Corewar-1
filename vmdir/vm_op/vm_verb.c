/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_verb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 05:04:20 by lduval            #+#    #+#             */
/*   Updated: 2017/05/20 05:14:32 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void		vm_verb(t_vm_proc *proc, int *param, int *nb_octet)
{
	int i;

	i = 0;
	ft_printf("P %4d | %s", proc->nproc, g_op_tab[proc->next_op - 1].name);
	while (i < 3 && nb_octet[i])
	{
		if (nb_octet[i] == 1)
			ft_printf(" r%d", param[i]);
		else
			ft_printf(" %d", param[i]);
		i++;
	}
	ft_printf("\n");
}

