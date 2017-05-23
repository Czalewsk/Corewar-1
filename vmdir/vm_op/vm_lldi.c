/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:48:36 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 00:17:02 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_lldi(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	int				i;
	int				tmp;

	if (!(ft_intisbetween_inc(param[2], 0, 15)
				&& (nb_octet[0] != 1 || ft_intisbetween_inc(param[0], 0, 15))
				&& (nb_octet[1] != 1 || ft_intisbetween_inc(param[1], 0, 15))))
		return ;
	i = 0;
	while (i < 2)
	{
		if (nb_octet[i] == 1)
			ft_memcpy(&(param[i]), proc->registre + (param[i] * REG_SIZE),
					REG_SIZE);
		else if (((proc->ocp >> (3 - i) * 2) & 3) == 3)
		{
			tmp = vm_get_param(data, proc->pc + (param[i]), REG_SIZE);
			ft_memcpy(&(param[i]), &tmp, REG_SIZE);
		}
		i++;
	}
	i = param[0] + param[1];
	tmp = vm_get_param(data, proc->pc + (i), REG_SIZE);
	ft_memcpy(proc->registre + param[2] * REG_SIZE, &tmp, REG_SIZE);
	proc->carry = (int)(tmp == 0);
	vm_verb(proc, param, nb_octet);
}
