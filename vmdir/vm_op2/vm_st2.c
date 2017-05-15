/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:57:47 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 05:04:23 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_st2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	int	i;
	int tmp;

	i = 1;
	if (ft_intisbetween_inc(param[0], 0, 15) && ((proc->ocp != 80) || ft_intisbetween_inc(param[1], 0, 15)))
	{
			ft_memcpy(&i, proc->registre + (param[0] * REG_SIZE), REG_SIZE);
			tmp =  ((proc->pc + (param[1] % IDX_MOD)) % MEM_SIZE);
			(proc->ocp == 80) ? ft_memcpy(proc->registre + param[1] * REG_SIZE, &i, REG_SIZE) :
			vm_set_param(data, tmp , (unsigned char *)&i, REG_SIZE);
	}
	(void)nb_octet;
}
