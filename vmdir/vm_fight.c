/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 23:22:43 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 08:57:03 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"
#include "vm_op/vm_op.h"

extern	t_op g_op_tab[];
void		(*g_vm_exec_op[17])(t_vm_data *, t_vm_proc *, int *, int *) =
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

static void	vm_get_param3(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	int i;

	i = (proc->ocp) ? 2 : 1;
	param[0] = vm_get_param(data, (proc->pc + i) % MEM_SIZE, nb_octet[0]);
	param[1] = vm_get_param(data, (proc->pc + i + nb_octet[0]) % MEM_SIZE, nb_octet[1]);
	param[2] = vm_get_param(data, (proc->pc + i + nb_octet[0] + nb_octet[1]) % MEM_SIZE, nb_octet[2]);
}

static int	vm_get_param2(t_vm_data *data, t_vm_proc *proc, int *nb_octet, int *param)
{
	int noct;

	ft_bzero(nb_octet, 4 * 3);
	ft_bzero(param, 4 * 3);
	if (proc->ocp)
	{
		noct = vm_get_nb_octet(nb_octet, proc->ocp, proc->next_op - 1);
	}
	else
	{
		noct = (proc->next_op == 1) ? 4 : 2;
		nb_octet[0] = noct;
	}
	vm_get_param3(data, proc, param, nb_octet);
	return (noct);
}

static void	vm_exec_op(t_vm_data *data, t_vm_proc *proc)
{
	int nb;
	int nb_octet[3];
	int param[3];
	int i;
	int nb2;

	proc->ocp = 0;
	i = 0;
	if (g_op_tab[(int)(proc->next_op - 1)].octet)
	{
		data->col_arena[(proc->pc + 1) % MEM_SIZE] |= 16;
		proc->ocp = data->arena[(proc->pc + 1) % MEM_SIZE];
		proc->ocp = (proc->ocp == 0) ? 1 : proc->ocp;
		i = 1;
	}
	nb = vm_get_param2(data, proc, nb_octet, param);
	nb2 = nb;
	while (nb2)
	{
		data->col_arena[(proc->pc + i + nb2) % MEM_SIZE] |= 64;
		nb2--;
	}
	if ((proc->ocp && vm_check_param(proc->ocp, proc->next_op - 1)) || !proc->ocp)
	{
		(*g_vm_exec_op[(int)proc->next_op - 1])(data, proc, param, nb_octet);
	}
	else if (proc->ocp && (data->option & VM_OPT_V))
		vm_adv_verb(proc, nb_octet);
	nb += proc->ocp ? 2 : 1;
	proc->pc += (proc->next_op) != 9 ? nb : 0;
}

static void	vm_exec_proc(t_vm_data *data)
{
	t_list		*tmp;
	t_vm_proc	*tmproc;

	tmp = data->tab_proc;
	while (tmp)
	{
		tmproc = (t_vm_proc *)tmp->content;
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
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", proc->nproc, data->nbr_cycle - proc->last_live, data->cycletodie);
		data->nb_proc--;
		return (1);
	}
	return (0);
}

static void	vm_check_live_proces(t_vm_data *data)
{
	ft_lst_remove_if(&(data->tab_proc), &vm_check_last_live, NULL);
	data->nb_proc = ft_lstlen(data->tab_proc);
	if (data->nbr_lives >= NBR_LIVE || data->lastcycledec == MAX_CHECKS)
	{
		data->lastcycledec = 0;
		data->cycletodie = !(data->cycletodie - CYCLE_DELTA < 1) ? data->cycletodie - CYCLE_DELTA : data->cycletodie;
		if (data->option & VM_OPT_V)
			ft_printf("Cycle to die is now %d\n", data->cycletodie);
	}
	else
		data->lastcycledec++;
	data->nbr_lives = 0;
}

/*void		vm_print_winner(t_vm_data *data)
{
	
	if (data->nbr_cycle == data->dump)
		//print_arena_32();
	else if (!data->option)
		ft_printf("le joueur %d(%s) a gagne\n",);
	//if (data->option & VM_OPT_S)
	else if (data->option & VM_OPT_V && data->winner)
		ft_printf("Conterstant %d, \"%s\", has won !\n");
}*/

void		vm_fight(void)
{
	int				finish;
	t_vm_data		*data;
	t_ncurses_data	ncurses_data;

	finish = 0;
	data = get_data();
	if (data->option & VM_OPT_G)
		vm_ncurses_init(data, &ncurses_data);
	while (!finish)
	{
		if (((data->nbr_cycle) == (data->dump)) || 0 == data->nb_proc)
			break;
		if (data->option)
		{
			if ((data->option & VM_OPT_V) && data->nbr_cycle != 0)
				ft_printf("It is now cycle %d\n", data->nbr_cycle);
			if (data->option & VM_OPT_G)
			{
				vm_ncurses(&ncurses_data);
				usleep(ncurses_data.interval);
			}
		}
		vm_exec_proc(data);
		if (data->nbr_cycle - data->lastcheck == data->cycletodie)
		{
			vm_check_live_proces(data);
			data->lastcheck = data->nbr_cycle;
		}
		data->nbr_cycle += 1;
	}
	if (data->option & VM_OPT_G)
		vm_ncurses_free();
//	vm_print_winner(data);
}
