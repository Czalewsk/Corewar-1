#include "vm_op.h"
void vm_fork(t_vm_data *data, t_vm_proc *proc, int pos)
{
    int param;
    t_list *temp;
    t_vm_proc fork;

    param = vm_get_param(data, pos + 1, 2);
    fork.beg = proc->pc + (param % IDX_MOD);
    fork.carry = proc->carry;
    fork.champ = proc->champ;
    fork.last_live = 0;
    fork.inproc = 0;
    ft_memcpy(fork.registre, proc->registre, REG_SIZE * REG_NUMBER);
    f (!(temp = ft_lstnew(&fork, sizeof(t_vm_proc))))
        ft_error("proc list malloc failed", &vm_free_all);
    data->nb_proc++;
    ft_lstadd(&(data->tab_proc), temp);
    ft_memcpy(data->arena + pos, proc->, );
}
