/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 12:33:48 by lduval            #+#    #+#             */
/*   Updated: 2017/05/26 12:52:48 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"
#include "vm_op/vm_op.h"

extern	t_op g_op_tab[];

void	(*g_vm_exec_op[17])(t_vm_data *, t_vm_proc *, int *, int *) =
{
	&vm_live,
	&vm_ld,
	&vm_st,
	&vm_add,
	&vm_sub,
	&vm_and,
	&vm_or,
	&vm_xor,
	&vm_zjmp,
	&vm_ldi,
	&vm_sti,
	&vm_fork,
	&vm_lld,
	&vm_lldi,
	&vm_lfork,
	&vm_aff,
	NULL
};

static void	vm_get_param3(t_vm_data *data, t_vm_proc *proc,
		int *param, int *nb_octet)
{
	int i;

	i = (proc->ocp) ? 2 : 1;
	param[0] = vm_get_param(data, (proc->pc + i) % MEM_SIZE, nb_octet[0]);
	param[1] = vm_get_param(data,
			(proc->pc + i + nb_octet[0]) % MEM_SIZE, nb_octet[1]);
	param[2] = vm_get_param(data,
		(proc->pc + i + nb_octet[0] + nb_octet[1]) % MEM_SIZE, nb_octet[2]);
}

static int	vm_get_param2(t_vm_data *data, t_vm_proc *proc,
		int *nb_octet, int *param)
{
	int noct;

	ft_bzero(nb_octet, 4 * 3);
	ft_bzero(param, 4 * 3);
	if (proc->ocp)
	{
		noct = vm_get_nb_octet(nb_octet, proc->ocp, proc->next_op - 1);
	}
	else
	{
		noct = (proc->next_op == 1) ? 4 : 2;
		nb_octet[0] = noct;
	}
	vm_get_param3(data, proc, param, nb_octet);
	return (noct);
}

void		vm_exec_op(t_vm_data *data, t_vm_proc *proc)
{
	int nb;
	int nb_octet[3];
	int param[3];
	int i;
	int nb2;

	proc->ocp = 0;
	i = 0;
	if (g_op_tab[(int)(proc->next_op - 1)].octet && (i = 1))
	{
		data->col_arena[(proc->pc + 1) % MEM_SIZE] |= 16;
		proc->ocp = data->arena[(proc->pc + 1) % MEM_SIZE];
		proc->ocp = (proc->ocp == 0) ? 1 : proc->ocp;
	}
	nb = vm_get_param2(data, proc, nb_octet, param);
	nb2 = nb + 1;
	while (--nb2)
		data->col_arena[(proc->pc + i + nb2) % MEM_SIZE] |= 64;
	if ((proc->ocp && vm_check_param(proc->ocp, proc->next_op - 1))
			|| !proc->ocp)
		(*g_vm_exec_op[(int)proc->next_op - 1])(data, proc, param, nb_octet);
	else if (proc->ocp && (data->option & VM_OPT_V))
		vm_adv_verb(proc, nb_octet);
	nb += proc->ocp ? 2 : 1;
	proc->pc += (proc->next_op) != 9 ? nb : 0;
}
