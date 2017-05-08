/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 23:22:43 by lduval            #+#    #+#             */
/*   Updated: 2017/05/08 18:26:59 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"
#include "vm_op/vm_op.h"

extern	t_op g_op_tab[];

void		(*g_vm_exec_op[17])(t_vm_data *, t_vm_proc *, int) =
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

static void	vm_exec_proc(t_vm_data *data)
{
	t_list		*tmp;
	t_vm_proc	*tmproc;

	tmp = data->tab_proc;
	while (tmp)
	{
		tmproc = (t_vm_proc *)tmp->content;
		data->col_arena[(tmproc->pc + tmproc->beg) % MEM_SIZE] -= 4;
		if (!tmproc->in_proc)
		{
			if (tmproc->next_op > 0 && tmproc->next_op < 17)
				(*g_vm_exec_op[(int)tmproc->next_op - 1])(data,
						tmproc, (tmproc->beg + tmproc->pc));
			else
				tmproc->pc++;
			tmproc->next_op = data->arena[(tmproc->beg + tmproc->pc) % MEM_SIZE];
			tmproc->in_proc = (tmproc->next_op > 0 && tmproc->next_op < 17) ?
				g_op_tab[(int)tmproc->next_op - 1].nb_cycle : 0;
		}
		else
			(tmproc->in_proc)--;
		data->col_arena[(tmproc->pc + tmproc->beg) % MEM_SIZE] += 4;
		tmp = tmp->next;
	}
}

static int	vm_check_last_live(t_list *l)
{
	t_vm_data	*data;
	t_vm_proc	*proc;

	data = get_data();
	proc = (t_vm_proc *)l->content;
	if (data->nbr_cycle - proc->last_live >= CYCLE_TO_DIE)
		return (1);
	return (0);
}

static void	vm_check_live_proces(t_vm_data *data)
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

void		vm_fight(void)
{
	int			finish;
	int			i;
	t_vm_data	*data;

	finish = 0;
	i = 0;
	data = get_data();
	ft_printf("nbr_cycle: %d, nbr_proc: %d\n", data->nbr_cycle, data->nb_proc);
	while (!finish)
	{
		if (!(data->nbr_cycle % data->cycletodie))
			vm_check_live_proces(data);
		if (data->option & VM_OPT_G)
		{
			system("clear");
			vm_print_arena();
			//ft_putnbr(i);
			ft_printf("nbr_cycle: %d, nbr_proc: %d", data->nbr_cycle, data->nb_proc);
			ft_putendl("");
//			usleep(20000);
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
