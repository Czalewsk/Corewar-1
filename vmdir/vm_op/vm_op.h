#ifndef VM_OP_H
# define VM_OP_H

#include "../vm_header.h"

int     vm_get_param(t_vm_data *data, int pos, int size_param);
void    vm_live(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_ld(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_st(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_add(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_sub(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_and(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_or(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_xor(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_zjmp(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_ldi(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_sti(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_fork(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_lld(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_lldi(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_lfork(t_vm_data *data, t_vm_proc *proc, int pos);
void    vm_aff(t_vm_data *data, t_vm_proc *proc, int pos);


#endif
