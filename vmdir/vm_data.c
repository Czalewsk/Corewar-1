/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 01:41:04 by lduval            #+#    #+#             */
/*   Updated: 2017/05/02 23:18:24 by lduval           ###   ########.fr       */
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
		data->dump = -1;
		while (i < MAX_PLAYERS + 1)
		{
			data->tab_champ[i] = NULL;
			i++;
		}
		data->tab_proc = NULL;
		data->option = 0;
		data->nbr_lives = 0;
		data->cycletodie = CYCLE_TO_DIE;
		data->lastcycledec = 0;
		data->nbr_cycle = 0;
		data->nb_proc = 0;
		data->winner = NULL;
	}
	return (data);
}

void		vm_free_all(void)
{
	t_vm_data *data;

	data = get_data();
	if (data)
		free(data);
}
