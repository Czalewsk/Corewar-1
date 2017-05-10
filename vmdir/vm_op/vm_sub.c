/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:00:13 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 03:19:05 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_sub(t_vm_data *data, t_vm_proc *proc, int pos)
{
	int i;
	int param[3];
	int nb_octet[3];
	int ocp;
	int j;

	i = 0;
	ocp = (int)data->arena[(pos + 1) % MEM_SIZE];
	proc->pc += vm_get_nb_octet(nb_octet, ocp, 4);
	if (ocp != 84)
		return ;
	while (i < 3)
	{
		param[i] = vm_get_param(data, (pos + i + 2) % MEM_SIZE, 1);
		i++;
	}
	i = 1;
	if (ft_intisbetween_inc(param[0], 0, 15) && ft_intisbetween_inc(param[1], 0, 15)
			&& ft_intisbetween_inc(param[2], 0, 15))
	{
		ft_memcpy(&i, proc->registre + (param[0] * REG_SIZE), REG_SIZE);
		ft_memcpy(&j, proc->registre + (param[1] * REG_SIZE), REG_SIZE);
		i -= j;
		ft_memcpy(proc->registre + param[2] * REG_SIZE, &i, REG_SIZE);
	}
	proc->carry = (int)(i == 0);
}
