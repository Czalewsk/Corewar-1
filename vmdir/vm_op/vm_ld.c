/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:41:20 by lduval            #+#    #+#             */
/*   Updated: 2017/05/03 09:43:00 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_ld(t_vm_data *data, t_vm_proc *proc, int pos)
{
	int	i;
	int	param[3];
	int	nb_octet[3];
	int	ocp;

	i = 0;
	ocp = (int)data->arena[(pos + 1) % MEM_SIZE];
	proc->pc += vm_get_nb_octet(nb_octet, ocp, 1);
	if (ocp != 24 || ocp != 28)
		return ;
	param[0] = vm_get_param(data, (pos + 2) % MEM_SIZE, nb_octet[0]);
	param[1] = vm_get_param(data, (pos + 2 + nb_octet[0]) % MEM_SIZE, nb_octet[1]);
	i = 1;
	if (ft_intisbetween_inc(param[1], 0, 15))
	{
		i = (ocp == 28) ? vm_get_param(data, (pos) + (param[0] % IDX_MOD), 4) : param[0];
		ft_memcpy(proc->registre + param[1] * REG_SIZE, &i, REG_SIZE);
	}
	proc->carry = (int)(i == 0);
}
