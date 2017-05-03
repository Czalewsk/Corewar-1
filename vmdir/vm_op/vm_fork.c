/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:36:51 by lduval            #+#    #+#             */
/*   Updated: 2017/05/03 12:12:15 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_fork(t_vm_data *data, t_vm_proc *proc, int pos)
{
	int			param;
	t_list		*temp;
	t_vm_proc	fork;

	param = vm_get_param(data, pos + 1, 2);
	fork.beg = (proc->beg + proc->pc + (param % IDX_MOD)) % MEM_SIZE;
	fork.carry = proc->carry;
	fork.champ = proc->champ;
	fork.last_live = 0;
	fork.in_proc = 0;
	fork.prog = proc->prog;
	fork.progsize = proc->progsize;
	ft_memcpy(fork.registre, proc->registre, REG_SIZE * REG_NUMBER);
	if (!(temp = ft_lstnew(&fork, sizeof(t_vm_proc))))
		ft_error("proc list malloc failed", &vm_free_all);
	data->nb_proc++;
	ft_lstadd(&(data->tab_proc), temp);
	ft_memcpy(data->arena + fork.beg, proc->prog, proc->progsize);
}
