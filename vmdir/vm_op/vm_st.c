
#include "vm_op.h"
void vm_st(t_vm_data *data, t_vm_proc *proc, int pos)
{
    int i = 0;
    int param[3];
    int nb_octet[3];
    int ocp;

    ocp = (int)data->arena[(pos + 1) % MEM_SIZE];
    proc->pc += vm_get_nb_octet(nb_octet, ocp, 2);
    if (ocp != 20 || ocp != 52)
        return ;
    param[0] = vm_get_param(data , (pos + 2) % MEM_SIZE, nb_octet[0]);
    param[1] = vm_get_param(data, (pos + 2 + nb_octet[0]) % MEM_SIZE, nb_octet[1]);
    i = 1;
    if (ft_intisbetween_inc(param[0], 0, 15) && ((ocp != 20) || ft_intisbetween_inc(param[1], 0, 15)))
    {
        i = param[0];
        (ocp == 20) ? ft_memcpy(proc->registre + param[1] * REG_SIZE, &i, REG_SIZE) :
            ft_memcpy((data->arena) + (pos + (param[1] % IDX_MOD)) , &i, REG_SIZE);
    }
    proc->carry = (int)(i == 0);
}
