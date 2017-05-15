/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:54:43 by lduval            #+#    #+#             */
/*   Updated: 2017/05/08 18:20:15 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_OP2_H
# define VM_OP2_H

# include "../vm_header.h"

extern	t_op g_op_tab[];

void	vm_set_param(t_vm_data *data, unsigned int pos,int num, int length);
void	vm_set_color(t_vm_data *data, unsigned int pos,unsigned char *s, int length);
int	vm_get_param(t_vm_data *data, unsigned int pos, int size_param);
void	vm_live2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_ld2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_st2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_add2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_sub2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_and2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_or2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_xor2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_zjmp2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_ldi2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_sti2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_fork2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_lld2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_lldi2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_lfork2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);
void	vm_aff2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet);

#endif
