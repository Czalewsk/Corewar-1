/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 11:38:40 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/05 20:28:28 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

int			vm_get_param(t_vm_data *data, int pos, int length)
{
	int					res;
	unsigned	char	value[5];
	int					i;

	i = 4;
	res = 0;
	if (!data || length <= 0 || length > 4)
		return (0);
	value[4] = '\0';
	while (--i >= 0)
	{
		if (i < length)
		{
			value[i] = data->arena[(pos + i) % MEM_SIZE];
		}
		else
			value[i] = 0;
	}
	res = ft_atoi_base((char*)value, "0123456789abcdef");
	return (res);
}
