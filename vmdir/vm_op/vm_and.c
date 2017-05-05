/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:21:22 by lduval            #+#    #+#             */
/*   Updated: 2017/05/05 19:52:09 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_and(t_vm_data *data, t_vm_proc *proc, int pos)
{
	int				i;
	int				param[3];
	int				nb_octet[3];
	unsigned int	ocp;
	int				tmp;

	i = 0;
	ocp = (unsigned int)data->arena[(pos + 1) % MEM_SIZE];
	proc->pc += vm_get_nb_octet(nb_octet, ocp, 5);
	ft_printf("LOL\n");
	if (!vm_check_param(ocp, 5))
		return ;
	ft_printf("nb_octet[0]=%i\n", nb_octet[0]);
	ft_printf("nb_octet[1]=%i\n", nb_octet[1]);
	ft_printf("nb_octet[2]=%i\n", nb_octet[2]);
	param[0] = vm_get_param(data, (pos + 2) % MEM_SIZE, nb_octet[0]);
	param[1] = vm_get_param(data, (pos + 2 + nb_octet[0]) % MEM_SIZE, nb_octet[1]);
	param[2] = vm_get_param(data, pos + 2 + nb_octet[0] + nb_octet[1], nb_octet[2]);
	ft_printf("param[0]=%i\n", param[0]);
	ft_printf("param[1]=%i\n", param[1]);
	ft_printf("param[2]=%i\n", param[2]);
	i = 1;
	if (ft_intisbetween_inc(param[2], 0, 15) && (((ocp >> 2) & 3) != 1 || ft_intisbetween_inc(param[0], 0, 15))
			&& (((ocp >> 4) & 3) != 1 || ft_intisbetween_inc(param[1], 0, 15)))
	{
		while (i < 3)
		{
			if (((ocp >> (2 * (i + 1))) & 3) == 1)
				param[i] = ft_atoi_bigendian(proc->registre + (param[i] * REG_SIZE), REG_SIZE);
			else
			{
				tmp = vm_get_param(data, pos + (param[i] % IDX_MOD) ,REG_SIZE);
				(((ocp >> (2 * (i + 1))) & 3) == 2) ? NULL : ft_memcpy(param + i, &tmp ,  REG_SIZE);
			}
			i++;
		}
		i = param[0] & param[1];
		ft_memcpy(proc->registre + param[2] * REG_SIZE, &i, sizeof(i));
	}
	proc->carry = (int)(i == 0);
}
