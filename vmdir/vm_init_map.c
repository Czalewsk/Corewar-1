/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 00:54:44 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 10:02:51 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"
#include "vm_op/vm_op.h"

static void		vm_init_proc(t_vm_data *data, t_vm_champ *champ, int pos)
{
	t_list		*temp;
	t_vm_proc	proc;
	static int	i = 0;
	int j = 0;

	proc.carry = 0;
	proc.champ = champ->num;
	proc.last_live = 0;
	proc.pc = pos;
	proc.in_proc = 0;
	proc.next_op = champ->prog[0];
	proc.in_proc = (proc.next_op > 0 && proc.next_op < 17) ?
				g_op_tab[(int)proc.next_op - 1].nb_cycle : 0;
	// mettre les registre a 0 avec bzero
	ft_bzero(proc.registre, REG_SIZE * (REG_NUMBER));
	ft_printf("%d num\n", champ->num);
	j = (champ->num);
	ft_memcpy(proc.registre + (1 * REG_SIZE), &j, REG_SIZE);
	//ft_printf("%d, %d\n", pos, champ->header.prog_size);
	proc.ocp = 0;
	if (!(temp = ft_lstnew(&proc, sizeof(t_vm_proc))))
		ft_error("proc list malloc failed", &vm_free_all);
	data->nb_proc++;
	ft_lstadd(&(data->tab_proc), temp);
	ft_memcpy(data->arena + pos, champ->prog, champ->header.prog_size);
	ft_memset(data->col_arena + pos, ft_power(2, i), champ->header.prog_size);
	i++;
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
		vm_init_proc(data, data->tab_champ[i], (i * MEM_SIZE) / n);
		i++;
	}
}

void			vm_init_arena(void)
{
	t_vm_data	*data;
	int			i;

	data = get_data();
	i = 0;
	while (i < MEM_SIZE)
	{
		data->arena[i] = 0;
		i++;
	}
	vm_init_champ(data);
}
