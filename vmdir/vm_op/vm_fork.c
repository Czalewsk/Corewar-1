/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:36:51 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 14:29:14 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_fork(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	t_list		*temp;
	t_vm_proc	fork;

	fork.pc = proc->pc + (param[0] % IDX_MOD);
	fork.pc = fork.pc >= 0 ? fork.pc : fork.pc + MEM_SIZE;
	fork.carry = proc->carry;
	fork.champ = proc->champ;
	fork.color = proc->color;
	fork.last_live = proc->last_live;
	fork.next_op = data->arena[(fork.pc) % MEM_SIZE];
	fork.in_proc = (fork.next_op > 0 && fork.next_op < 17) ?
		g_op_tab[(int)fork.next_op - 1].nb_cycle - 1 : 0;
	fork.progsize = proc->progsize;
	ft_memcpy(fork.registre, proc->registre, REG_SIZE * REG_NUMBER);
	data->nb_proc++;
	fork.nproc = data->nb_proc;
	if (!(temp = ft_lstnew(&fork, sizeof(t_vm_proc))))
		ft_error("proc list malloc failed", &vm_free_all);
	ft_lstadd(&(data->tab_proc), temp);
	vm_verb(proc, param, nb_octet);
	(void)nb_octet;
}
