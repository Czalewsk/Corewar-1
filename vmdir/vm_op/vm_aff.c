/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:42:52 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 07:03:22 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_aff(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	unsigned int	i;
	char			s[7] = "say ";

	if (!(ft_intisbetween_inc(param[0], 0 ,15)))
		return ;
	ft_memcpy(&i, proc->registre + (param[0] * REG_SIZE), REG_SIZE);
	data->affchar = (i % 256);
	if (data->option & VM_OPT_S)
	{
		s[5] = data->affchar;
		s[6] = '\0';
		system(s);
	}
	if (data->option & VM_OPT_S || !data->option)
		ft_printf("%c\n", data->affchar);
	(void)nb_octet;
	vm_verb(proc, param, nb_octet);
}
