/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 11:38:40 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/30 12:36:51 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

int			vm_get_param(t_vm_data *data, int pos, int length)
{
	int					res;
	unsigned	char	value[4];
	int					i;

	i = 4;
	res = 0;
	if (!data || length <= 0 || length > 4)
		return (0);
	while (--i >= 0)
	{
		if (i < length)
		{
			value[i] = data->arena[pos % MEM_SIZE];
			pos++;
		}
		else
			value[i] = 0;
	}
	res = ft_atoi_bigendian(value, 4);
	return (res);
}
