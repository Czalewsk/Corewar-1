/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_nb_octet.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:11:20 by lduval            #+#    #+#             */
/*   Updated: 2017/05/05 19:38:19 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

int		vm_get_nb_octet(int *nb_octet, unsigned int ocp, int nop)
{
	int	noct;
	int	i;
	int	tocp;

	i = 0;
	noct = 0;
	if (!((ocp & 1) == 1 || ((ocp >> 1) & 1) == 1))
	{
		while (i < g_op_tab[nop].nb_p)
		{
			tocp = (ocp >> (2 * (i + 1)) & 3);
			if (tocp == 1)
				nb_octet[i] = REG_SIZE;
			else if (tocp == 2)
				nb_octet[i] = g_op_tab[i].index ? IND_SIZE : DIR_SIZE;
			else if (tocp == 3)
				nb_octet[i] = IND_SIZE;
			else
				nb_octet[i] = 0;
			noct += nb_octet[i];
			i++;
		}
	}
	return (noct + 2);
}
