/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 01:41:04 by lduval            #+#    #+#             */
/*   Updated: 2017/03/28 05:41:07 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

t_vm_data	*get_data(void)
{
    int i;
	static t_vm_data *data = NULL;

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
