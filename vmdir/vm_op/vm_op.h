/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:54:43 by lduval            #+#    #+#             */
/*   Updated: 2017/05/16 17:44:51 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_OP_H
# define VM_OP_H

# include "../vm_header.h"

extern	t_op g_op_tab[];

int		vm_check_param(int ocp, unsigned int n_op);
int		vm_get_nb_octet(int *nb_octet, unsigned int ocp, int nop);
void	vm_set_color(t_vm_data *data, unsigned int pos, int num, int length);
void	vm_set_param(t_vm_data *data, unsigned int pos,
		unsigned char *s, int length);
int		vm_get_param(t_vm_data *data, unsigned int pos, int size_param);
void	vm_live(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_ld(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_st(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_add(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_sub(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_and(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_or(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_xor(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_zjmp(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_ldi(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_sti(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_fork(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_lld(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_lldi(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_lfork(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_aff(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);

#endif
