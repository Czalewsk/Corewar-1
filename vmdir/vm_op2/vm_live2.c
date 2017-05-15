/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:46:29 by lduval            #+#    #+#             */
/*   Updated: 2017/05/08 02:31:33 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void		vm_live2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	int		i;
	char	*nchamp;

	i = 0;
	nchamp = NULL;
	while (NULL == nchamp && data->tab_champ[i])
	{
		if (data->tab_champ[i]->num == param[0])
			nchamp = data->tab_champ[i]->name;
		i++;
	}
	if (data->option == 0)
	{
		if (nchamp)
			ft_printf("un processus dit que le joueur %s est en vie\n", nchamp);
		else
			ft_printf("un processus dit qu'un joueur inconnue de numero %d est en vie\n", param[0]);
	}
	proc->last_live = data->nbr_cycle;
	data->nbr_lives++;
	data->winner = nchamp ? nchamp : data->winner;
	(void)nb_octet;
}
