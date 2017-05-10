/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:57:47 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 02:03:07 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_st(t_vm_data *data, t_vm_proc *proc, int pos)
{
	int	i;
	int	param[3];
	int	nb_octet[3];
	int	ocp;
	int tmp;

	i = 0;
	ocp = (int)data->arena[(pos + 1) % MEM_SIZE];
	proc->pc += vm_get_nb_octet(nb_octet, ocp, 2);
	if (ocp != 112 && ocp != 80)
		return ;
	param[0] = vm_get_param(data, (pos + 2) % MEM_SIZE, nb_octet[0]);
	param[1] = vm_get_param(data, (pos + 2 + nb_octet[0]) % MEM_SIZE, nb_octet[1]);
	i = 1;
	if (ft_intisbetween_inc(param[0], 0, 15) && ((ocp != 80) || ft_intisbetween_inc(param[1], 0, 15)))
	{
			ft_memcpy(&i, proc->registre + (param[0] * REG_SIZE), REG_SIZE);
			tmp =  ((pos + (param[1] % IDX_MOD)) % MEM_SIZE);
			(ocp == 80) ? ft_memcpy(proc->registre + param[1] * REG_SIZE, &i, REG_SIZE) :
			vm_set_param(data, tmp , (unsigned char *)&i, REG_SIZE);
	}
	proc->carry = (int)(i == 0);
}
