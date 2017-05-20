/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:42:52 by lduval            #+#    #+#             */
/*   Updated: 2017/05/20 05:18:12 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_aff(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	(void)data;
	(void)proc;
	(void)param;
	(void)nb_octet;
	vm_verb(proc, param, nb_octet);
	return ;
}
