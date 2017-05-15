/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:41:20 by lduval            #+#    #+#             */
/*   Updated: 2017/05/06 16:50:32 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_ld2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	int	i;

	i = 0;
	if (ft_intisbetween_inc(param[1], 0, 15))
	{
		i = (proc->ocp == 208) ? vm_get_param(data, (proc->pc) + (param[0] % IDX_MOD), 4) : param[0];
		ft_memcpy(proc->registre + param[1] * REG_SIZE, &i, REG_SIZE);
	}
	proc->carry = (int)(i == 0);
	(void)nb_octet;
}