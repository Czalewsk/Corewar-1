/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:55:52 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 03:19:12 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_or2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	int				i;
	int				tmp;

	i = 1;
	if (ft_intisbetween_inc(param[2], 0, 15) && (nb_octet[0] != 1 || ft_intisbetween_inc(param[0], 0, 15))
			&& (nb_octet[1] != 1 || ft_intisbetween_inc(param[1], 0, 15)))
	{
		i = 0;
		while (i < 2)
		{
			if (nb_octet[i] == 1)
				ft_memcpy(&(param[i]), proc->registre + (param[i] * REG_SIZE), REG_SIZE);
			else if (nb_octet[i] == 2)
			{
				tmp = vm_get_param(data, proc->ocp + (param[i] % IDX_MOD) ,REG_SIZE);
				ft_memcpy(&(param[i]), &tmp , REG_SIZE);
			}
			i++;
		}
		i = param[0] | param[1];
		ft_memcpy(proc->registre + param[2] * REG_SIZE, &i, REG_SIZE);
	}
	proc->carry = (int)(i == 0);
}
