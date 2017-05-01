#include "vm_op.h"
void vm_ld(t_vm_data *data, t_vm_proc *proc, int pos)
{
    int i = 0;
    int param[3];
    int nb_octet[3];
    int ocp;

    ocp = (int)data->arena[(pos + 1) % MEM_SIZE];
    proc->pc += vm_get_nb_octet(nb_octet, ocp, 1);
    if (ocp != 24 || ocp != 28)
        return ;
    while (i < 2)
    {
        param[i] = vm_get_param(data , (pos + i + 2) % MEM_SIZE, nb_octet[i]);
        i++;
    }
    i = 1;
    if (ft_intisbetween_inc(param[1], 0, 15))
    {
        i = (ocp == 28) ? vm_get_param(data, (pos + 1) + (param[0] % IDX_MOD), 4) : parma[0];
        ft_memcpy(proc->registre + param[1] * REG_SIZE, i, REG_SIZE);
    }
    proc->carry = (int)(i == 0);
}
