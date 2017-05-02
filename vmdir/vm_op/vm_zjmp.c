#include "vm_op.h"

void vm_zjmp(t_vm_data *data, t_vm_proc *proc, int pos)
{
    int param;

    param = vm_get_param(data, pos + 1, 2)
    if (proc->pc == 1)
        proc->pc += param;
    else
        proc-> += 2;
}
