/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:58:45 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 10:15:36 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_sti2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	int				i;
	int				tmp;

	i = 1;
	if (ft_intisbetween_inc(param[0], 0, 15) && (nb_octet[1] != 1 || ft_intisbetween_inc(param[1], 0, 15)) && (nb_octet[2] != 1 || ft_intisbetween_inc(param[2], 0, 15)))
	{
		while (i < 3)
		{
			if (nb_octet[i] == 1)
				ft_memcpy(&(param[i]), proc->registre + (param[i] * REG_SIZE), REG_SIZE);
			else if (((proc->ocp >> (3 - i) * 2) & 3) == 3)
			{
				tmp = vm_get_param(data, proc->pc + (param[i] % IDX_MOD) ,REG_SIZE);
				ft_printf("\n%d", tmp);
				ft_memcpy(&(param[i]), &tmp , REG_SIZE);
			}
			i++;
		}
		i = param[1] + param[2];
		vm_set_param(data, proc->pc + i % MEM_SIZE, proc->registre + param[0] * REG_SIZE, REG_SIZE);
		ft_memcpy(&i, proc->registre + (param[0] * REG_SIZE), REG_SIZE);
	}
}

