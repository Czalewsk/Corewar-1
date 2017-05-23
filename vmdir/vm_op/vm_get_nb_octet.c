/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_nb_octet.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:11:20 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 06:24:07 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

int		vm_get_nb_octet(int *nb_octet, unsigned int ocp, int nop)
{
	int				noct;
	int				i;
	unsigned int	tocp;
	int				j;

	j = g_op_tab[nop].nb_p;
	i = 0;
	noct = 0;
	while (i < j)
	{
		tocp = (ocp >> ((3 - i) * 2)) & 3;
		if (tocp == 1)
			nb_octet[i] = 1;
		else if (tocp == 2)
			nb_octet[i] = g_op_tab[nop].index ? 2 : 4;
		else if (tocp == 3)
			nb_octet[i] = 2;
		else
			nb_octet[i] = 0;
		noct += nb_octet[i];
		i++;
	}
	return (noct);
}
