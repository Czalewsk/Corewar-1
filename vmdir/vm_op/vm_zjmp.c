/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:05:46 by lduval            #+#    #+#             */
/*   Updated: 2017/05/03 10:08:49 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_zjmp(t_vm_data *data, t_vm_proc *proc, int pos)
{
	int param;

	param = vm_get_param(data, pos + 1, 2);
	if (proc->pc == 1)
		proc->pc += param;
	else
		proc->pc += 2;
}
