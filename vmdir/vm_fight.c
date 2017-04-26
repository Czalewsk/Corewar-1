#include "vm_header.h"

int vm_check_last_live(t_list *l)
{
    t_vm_data   *data;
    t_vm_proc   *proc;

    data = get_data();
    proc = (t_vm_proc *)l->content;
    if (data->nbr_cycle - proc->last_live >= CYCLE_TO_DIE)
        return 1;
    return 0;
}
static void vm_check_live_proces(t_vm_data *data)
{
    ft_lst_remove_if(&(data->tab_proc), &vm_check_last_live, NULL);
    data->nb_proc = ft_lstlen(data->tab_proc);
    if (data->nbr_lives >= NBR_LIVE || data->lastcycledec == MAX_CHECKS)
    {
        data->lastcycledec = 0;
        data->cycletodie -= CYCLE_DELTA;
    }
    else
        data->lastcycledec++;
}

void vm_fight(void)
{
    int         finish;
    int         i;
    t_vm_data   *data;

    finish = 0;
    i = 0;
    data = get_data();
    ft_printf("nbr_cycle: %d, nbr_proc: %d", data->nbr_cycle,data->nb_proc);
    while (!finish)
    {
        if (!(data->nbr_cycle % data->cycletodie))
            vm_check_live_proces(data);
        if (data->option & VM_OPT_G)
        {
            //system("clear");
            //vm_print_arena();
            //ft_putnbr(i);
            ft_printf("nbr_cycle: %d, nbr_proc: %d", data->nbr_cycle,data->nb_proc);
            ft_putendl("");
            i++;
        }
        if (((data->nbr_cycle) == (data->dump)) || 0 == data->nb_proc)
            finish = 1;
        data->nbr_cycle += 1;
    }
    //vm_print_arena();
    //ft_putnbr(data->dump);
    //vm_print_winner(data);
}
