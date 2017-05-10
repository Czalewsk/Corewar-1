/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:36:51 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 10:03:54 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_fork(t_vm_data *data, t_vm_proc *proc, int pos)
{
	int			param;
	t_list		*temp;
	t_vm_proc	fork;

	param = vm_get_param(data, pos + 1, 2);
	fork.pc = proc->pc + (param % IDX_MOD);
	fork.pc = fork.pc >= 0 ? fork.pc : fork.pc + MEM_SIZE;
	fork.carry = proc->carry;
	fork.champ = proc->champ;
	fork.last_live = proc->last_live;
	fork.next_op = data->arena[(fork.pc) % MEM_SIZE];
	fork.in_proc = (fork.next_op > 0 && fork.next_op < 17) ?
		g_op_tab[(int)fork.next_op - 1].nb_cycle : 0;
	fork.prog = proc->prog;
	fork.progsize = proc->progsize;
	ft_memcpy(fork.registre, proc->registre, REG_SIZE * REG_NUMBER);
	if (!(temp = ft_lstnew(&fork, sizeof(t_vm_proc))))
		ft_error("proc list malloc failed", &vm_free_all);
	data->nb_proc++;
	ft_lstadd(&(data->tab_proc), temp);
	proc->pc += 3;
}
