/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 01:41:04 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 11:45:14 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

t_vm_data	*get_data(void)
{
	int					i;
	static t_vm_data	*data = NULL;

	i = 0;
	if (!data)
	{
		if (!(data = (t_vm_data *)malloc(sizeof(t_vm_data))))
			ft_error("malloc failed in t_vm_data", NULL);
		ft_bzero(&(data->tab_champ), sizeof(t_vm_data *) * (MAX_PLAYERS + 1));
		data->nbr_cycle = 0;
		data->nbr_lives = 0;
		data->cycletodie = CYCLE_TO_DIE;
		data->lastcycledec = 0;
		data->option = 0;
		data->dump = -1;
		data->tab_proc = NULL;
		data->nb_proc = 0;
		data->winner = 0;
		data->lastcheck = 0;
		ft_bzero(data->col_arena, MEM_SIZE);
		ft_bzero(data->arena, MEM_SIZE);
	}
	return (data);
}

void		del_tab_proc(void *content, size_t size)
{
	(void)size;
	ft_printf("DELETE\n");
	free(content);
}

void		vm_free_all(void)
{
	t_vm_data	*data;
	int			i;

	i = 0;
	data = get_data();
	while (data->tab_champ[i])
	{
		free(data->tab_champ[i]->name);
		free(data->tab_champ[i]->prog);
		free(data->tab_champ[i]);
		++i;
	}
	if (data)
		free(data);
}
