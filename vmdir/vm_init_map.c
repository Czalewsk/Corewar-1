/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 00:54:44 by lduval            #+#    #+#             */
/*   Updated: 2017/05/26 11:55:59 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"
#include "vm_op/vm_op.h"

static void		vm_init_proc_ext(t_vm_proc *p, t_vm_champ *champ, int o, int i)
{
	p->carry = 0;
	p->champ = champ->num;
	p->last_live = 0;
	p->pc = o;
	p->color = i;
	p->in_proc = 0;
	p->next_op = champ->prog[0];
	p->in_proc = (p->next_op > 0 && p->next_op < 17) ?
				g_op_tab[(int)p->next_op - 1].nb_cycle : 0;
	ft_bzero(p->registre, REG_SIZE *(REG_NUMBER));
}

static void		vm_init_proc(t_vm_data *data, t_vm_champ *champ, int pos)
{
	t_list		*temp;
	t_vm_proc	proc;
	static int	i = 0;
	int			j;

	vm_init_proc_ext(&proc, champ, pos, i);
	j = (champ->num);
	ft_memcpy(proc.registre + (4), &j, 4);
	proc.ocp = 0;
	data->nb_proc++;
	proc.nproc = data->nb_proc;
	if (!(temp = ft_lstnew(&proc, sizeof(t_vm_proc))))
		ft_error("proc list malloc failed", &vm_free_all);
	ft_lstadd(&(data->tab_proc), temp);
	ft_memcpy(data->arena + pos, champ->prog, champ->header.prog_size);
	ft_memset(data->col_arena + pos, ft_power(2, i), champ->header.prog_size);
	i++;
	if (data->option & VM_OPT_V)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
i, champ->header.prog_size, champ->header.prog_name, champ->header.comment);
	champ->posnum = i;
}

static void		vm_init_champ(t_vm_data *data)
{
	int	i;
	int	n;

	n = 0;
	i = n;
	while (data->tab_champ[n])
		++n;
	while (data->tab_champ[i])
	{
		if (data->option & VM_OPT_S)
			ft_say(data->tab_champ[i]->header.prog_name);
		vm_init_proc(data, data->tab_champ[i], (i * MEM_SIZE) / n);
		i++;
		if (data->tab_champ[i] && (data->option & VM_OPT_S))
			ft_say(" versus");
	}
	if (data->option & VM_OPT_S)
	{
		ft_say(" fight");
		usleep(100000);
		ft_afplay("afplay vmdir/gampok.mp3");
	}
}

void			vm_init_arena(void)
{
	t_vm_data	*data;
	int			i;

	data = get_data();
	if (data->option & VM_OPT_V)
		ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < MEM_SIZE)
	{
		data->arena[i] = 0;
		i++;
	}
	vm_init_champ(data);
}
