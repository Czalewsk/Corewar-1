/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:12:50 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 06:22:15 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_add(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	int j;
	int i;

	i = 1;
	if (!(ft_intisbetween_inc(param[0], 0, 15)
				&& ft_intisbetween_inc(param[1], 0, 15)
				&& ft_intisbetween_inc(param[2], 0, 15)))
		return ;
	ft_memcpy(&j, proc->registre + (param[0] * REG_SIZE), REG_SIZE);
	ft_memcpy(&i, proc->registre + (param[1] * REG_SIZE), REG_SIZE);
	i += j;
	ft_memcpy(proc->registre + param[2] * REG_SIZE, &i, REG_SIZE);
	vm_verb(proc, param, nb_octet);
	(void)data;
	(void)nb_octet;
	proc->carry = (int)(i == 0);
}
