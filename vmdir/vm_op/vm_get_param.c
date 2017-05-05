/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 11:38:40 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/05 19:16:02 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

int			vm_get_param(t_vm_data *data, int pos, int length)
{
	int					res;
	unsigned	char	value[5];
	int					i;

	i = -1;
	res = 0;
	if (!data || length <= 0 || length > 4)
		return (0);
	value[4] = '\0';
	while (++i < 4)
	{
		if (4 - i <= length)
		{
			value[i] = data->arena[pos % MEM_SIZE];
			pos++;
		}
		else
			value[i] = 0;
	}
	res = ft_atoi((char*)value);
	return (res);
}
