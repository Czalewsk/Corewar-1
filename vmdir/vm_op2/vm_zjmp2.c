/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:05:46 by lduval            #+#    #+#             */
/*   Updated: 2017/05/08 15:28:07 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_zjmp2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{ 
	proc->pc += (proc->carry == 1) ? param[0] : 3;
	(void)nb_octet;
	(void)data;
}
