/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 11:38:40 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/11 03:57:59 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"
extern		t_op	g_op_tab[];
extern		void (*g_vm_exec_op[]);

int			vm_get_param(t_vm_data *data, t_vm_proc *proc, int *nb_octet,
		int *param)
{
	int		i;
	int		id_fx;
	int		ret;
	int		length;
	unsigned	char	val[5];

	i = 0;
	id_fx = data->arena[proc->pc] - 1;
	ret = vm_get_nb_octet(nb_octet, data->arena[(proc->pc + 1) % MEM_SIZE], id_fx);
	if (!vm_check_param(data->arena[(proc->pc + 1) % MEM_SIZE], id_fx))
		return (ret);
	while (i < g_op_tab[id_fx].nb_p && (length = nb_octet[i]))
	{
		while (--length >= 0)
			val[length] = data->arena[(proc->pc + length) % MEM_SIZE];
		param[i] = (nb_octet[i] == 2) ? (short)ft_atoi_bigendian(val,
				nb_octet[i]) : ft_atoi_bigendian(val, nb_octet[i]);
	}
	//EXEC DES PROCESSUS
	(*g_vm_exec_op[id_fx])(data, proc, proc->pc);
	return (ret);
}
/*
   int			vm_get_param(t_vm_data *data, unsigned int pos, int length)
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
   return ((length == 2) ? (short)res : res);
   }
   */
void			vm_set_param(t_vm_data *data, unsigned int pos,unsigned char *s, int length)
{
	int			i;

	i = 0;
	while (i <  length)
	{
		data->arena[(pos + length - (i + 1)) % MEM_SIZE] = s[i];
		i++;
	}
}
