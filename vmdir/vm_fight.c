#include "vm_header.h"
#include "lexer.h"
#include "vm_op/vm_op.h"

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

void     (*g_vm_exec_op[17])(t_vm_data *,t_vm_proc *,int ) =
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

static void vm_exec_proc(t_vm_data  *data)
{
    t_list      *tmp;
    t_vm_proc   *tmproc;

    tmp = data->tab_proc;
    while (tmp)
    {
        tmproc = (t_vm_proc *)tmp->content;
        if (!tmproc->in_proc)
        {
            if (tmproc->next_op >= 0 && tmproc->next_op < 17)
                (*g_vm_exec_op[tmproc->next_op])(data, tmproc, (tmproc->beg + tmproc->pc));
            else
                tmproc->pc++;
            tmproc->next_op = data->arena[(tmproc->beg + tmproc->pc) % MEM_SIZE];
            tmproc->in_proc = (tmproc->next_op >= 0 && tmproc->next_op < 17) ? op_tab[tmproc->next_op].nb_cycle : 0;
        }
        else
            (tmproc->in_proc)--;
        tmp = tmp->next;
    }
}

int     vm_get_param(t_vm_data *data, int pos, int size_param)
{
    return 1;
}

static int vm_check_last_live(t_list *l)
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
        vm_exec_proc(data);
        data->nbr_cycle += 1;
    }
    //vm_print_arena();
    //ft_putnbr(data->dump);
    //vm_print_winner(data);
}
