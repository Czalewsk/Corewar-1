/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 11:38:40 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/16 17:32:57 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

int		vm_get_param(t_vm_data *data, unsigned int pos, int length)
{
	int				res;
	unsigned char	value[4];
	int				i;

	res = 0;
	if (!data || length <= 0 || length > 4)
		return (0);
	i = length - 1;
	while (i >= 0)
	{
		value[i] = (int)data->arena[(pos + (i)) % MEM_SIZE];
		i--;
	}
	res = ft_atoi_bigendian(value, length);
	return ((length == 2) ? (short)res : res);
}

void	vm_set_param(t_vm_data *data, unsigned int pos,
		unsigned char *s, int length)
{
	int			i;

	i = 0;
	while (i < length)
	{
		data->arena[(pos + length - (i + 1)) % MEM_SIZE] = s[i];
		i++;
	}
}

void	vm_set_color(t_vm_data *data, unsigned int pos, int num, int length)
{
	int			i;

	i = 0;
	while (i < length)
	{
		data->col_arena[(pos + length - (i + 1)) % MEM_SIZE] |=
			ft_power(2, num);
		i++;
	}
}
