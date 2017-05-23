/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:05:46 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 01:27:35 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_zjmp(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	vm_verb(proc, param, nb_octet);
	proc->pc += (proc->carry == 1) ? param[0] : 3;
	while (proc->pc < 0)
		proc->pc += MEM_SIZE;
	while (proc->pc > MEM_SIZE)
		proc->pc -= MEM_SIZE;
	(void)nb_octet;
	(void)data;
}
