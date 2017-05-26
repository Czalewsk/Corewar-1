/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 23:22:43 by lduval            #+#    #+#             */
/*   Updated: 2017/05/26 17:30:40 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"
#include "vm_op/vm_op.h"

extern	t_op g_op_tab[];

static void	vm_exec_proc(t_vm_data *data, t_vm_proc *tmproc)
{
	t_list		*tmp;

	tmp = data->tab_proc;
	while (tmp && (tmproc = (t_vm_proc *)tmp->content))
	{
		data->col_arena[(tmproc->pc) % MEM_SIZE] &= ~128;
		if (!tmproc->in_proc)
		{
			if (tmproc->next_op > 0 && tmproc->next_op < 17)
				vm_exec_op(data, tmproc);
			else
				tmproc->pc++;
			while (tmproc->pc < 0)
				tmproc->pc += MEM_SIZE;
			while (tmproc->pc > MEM_SIZE)
				tmproc->pc -= MEM_SIZE;
			tmproc->next_op = data->arena[(tmproc->pc) % MEM_SIZE];
			tmproc->in_proc = (tmproc->next_op > 0 && tmproc->next_op < 17) ?
				g_op_tab[(int)tmproc->next_op - 1].nb_cycle - 1 : 0;
		}
		else
			(tmproc->in_proc)--;
		data->col_arena[(tmproc->pc) % MEM_SIZE] |= 128;
		tmp = tmp->next;
	}
}

static int	vm_check_last_live(t_list *l)
{
	t_vm_data	*data;
	t_vm_proc	*proc;

	data = get_data();
	proc = (t_vm_proc *)l->content;
	if (data->nbr_cycle - proc->last_live >= data->cycletodie)
	{
		if (data->option & VM_OPT_V)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			proc->nproc, data->nbr_cycle - proc->last_live, data->cycletodie);
		data->nb_proc--;
		return (1);
	}
	return (0);
}

static void	vm_check_live_proces(t_vm_data *data)
{
	ft_lst_remove_if(&(data->tab_proc), &vm_check_last_live, &del_tab_proc);
	data->nb_proc = ft_lstlen(data->tab_proc);
	data->lastcycledec++;
	if (data->nbr_lives >= NBR_LIVE || data->lastcycledec == MAX_CHECKS)
	{
		data->lastcycledec = 0;
		data->cycletodie = data->cycletodie - CYCLE_DELTA;
		if (data->option & VM_OPT_V)
			ft_printf("Cycle to die is now %d\n", data->cycletodie);
	}
	data->nbr_lives = 0;
}

static void	vm_fight_option(t_vm_data *data, t_ncurses_data ncurses_data)
{
	if ((data->option & VM_OPT_V) && data->nbr_cycle != 0)
		ft_printf("It is now cycle %d\n", data->nbr_cycle);
	if (data->option & VM_OPT_G)
	{
		vm_ncurses(&ncurses_data);
		usleep(ncurses_data.interval);
	}
}

void		vm_fight(void)
{
	int				finish;
	t_vm_data		*data;
	t_ncurses_data	ncurses_data;

	finish = 0;
	data = get_data();
	if (data->option & VM_OPT_G)
		vm_ncurses_init(data, &ncurses_data);
	while (data->cycletodie > 0)
	{
		if (((data->nbr_cycle) == (data->dump)) || 0 == data->nb_proc)
			break ;
		if (data->option)
			vm_fight_option(data, ncurses_data);
		vm_exec_proc(data, NULL);
		if (data->nbr_cycle - data->lastcheck == data->cycletodie)
		{
			vm_check_live_proces(data);
			data->lastcheck = data->nbr_cycle;
		}
		data->nbr_cycle += 1;
	}
	if (data->option & VM_OPT_G)
		vm_ncurses_free();
	vm_print_winner(data);
}
