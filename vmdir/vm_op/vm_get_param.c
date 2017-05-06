/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 11:38:40 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/06 07:12:15 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

int			vm_get_param(t_vm_data *data, int pos, int length)
{
	int					res;
	unsigned char	value[5];
	int					i;

	res = 0;
	if (!data || length <= 0 || length > 4)
		return (0);
	i = length - 1;
	value[i] = '\0';
	while (i >= 0)
	{
		value[i] = (int)data->arena[(pos + (i)) % MEM_SIZE];
		i--;
	}
	res = ft_atoi_bigendian(value, length);
	return (res);
}

void			vm_set_param(t_vm_data *data, int pos,unsigned char *s, int length)
{
	int			i;
	
	i = 0;
	while (i <  length)
	{
		data->arena[(pos + i) % MEM_SIZE] = s[i];
		i++;
	}
}

