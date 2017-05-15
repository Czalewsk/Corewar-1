/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:37:29 by lduval            #+#    #+#             */
/*   Updated: 2017/05/05 23:28:46 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

int	vm_check_param(int ocp, unsigned int n_op)
{
	int				i;
	unsigned int			tocp;
	unsigned char			ocp2;

	i = 0;
	if ((ocp & 1) == 1 || ((ocp >> 1) & 1) == 1)
		return (i);	
	ocp >>= 2;
	ocp2 = ocp << 2;
	while (i < 3 && ocp2 > 0)
	{
		if (i >= g_op_tab[n_op].nb_p)
			return (0);
		tocp = (ocp >> ((2 - i) * 2)) & 3;
		if (tocp == 1 && ((g_op_tab[n_op].type_param[i]) & T_REG) == 0)
			return (0);
		else if (tocp == 2 && ((g_op_tab[n_op].type_param[i]) & T_DIR) == 0)
			return (0);
		else if (tocp == 3 && ((g_op_tab[n_op].type_param[i]) & T_IND) == 0)
			return (0);
		else if (tocp == 0)
			return (0);
		i++;
		ocp2 <<= 2;
	}
	return (i == g_op_tab[n_op].nb_p);
}
