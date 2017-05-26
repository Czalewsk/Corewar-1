/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 16:11:57 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/26 16:14:35 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"
#include "vm_op/vm_op.h"

void		vm_print_winner(t_vm_data *data)
{
	if (data->nbr_cycle == data->dump)
		vm_print_arena();
	else if (data->winner > 0)
	{
		if (!data->option)
			ft_printf("le joueur %d(%s) a gagne\n",
			data->winner, data->tab_champ[data->winner - 1]->header.prog_name);
		if (data->option & VM_OPT_S)
		{
			ft_afplay("afplay vmdir/winpok.mp3");
			ft_say(data->tab_champ[data->winner - 1]->header.prog_name);
			ft_say("wins");
		}
		else if (data->option & VM_OPT_V && data->winner)
			ft_printf("Conterstant %d, \"%s\", has won !\n",
			data->winner, data->tab_champ[data->winner - 1]->header.prog_name);
	}
}
