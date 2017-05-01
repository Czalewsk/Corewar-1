/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 11:26:58 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/01 11:27:30 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void    vm_live(t_vm_data *data, t_vm_proc *proc, int pos)
{
    int     live;
    int     i;
    char    *nchamp;

    i = 0;
    nchamp = NULL;
    live = vm_get_param(data, pos + 1, 4);
    while (NULL == nchamp && data->tab_champ[i])
    {
        if (data->tab_champ[i]->num == live)
            nchamp = data->tab_champ[i]->name;
        i++;
    }
    if (data->option !=  0)
    {
        if (nchamp)
            ft_printf("un processus dit que le joueur %s est en vie\n", nchamp);
        else
            ft_printf("un processus dit qu'un joueur inconnue de numero %d est en vie", live);
    }
    proc->pc += 5;
    data->winner = nchamp;
}
