/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_pars_param2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:12:29 by lduval            #+#    #+#             */
/*   Updated: 2017/05/26 13:13:58 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

int		vm_fill_champion(char *champ_name, int n, t_vm_data *data)
{
	int i;

	i = 0;
	while (data->tab_champ[i])
		i++;
	if (i >= MAX_PLAYERS)
		ft_error("Too many player", &vm_free_all);
	if (!(data->tab_champ[i] = (t_vm_champ *)malloc(sizeof(t_vm_champ))))
		ft_error("malloc failed in vm_fill_champion()", &vm_free_all);
	if (!(data->tab_champ[i]->name = ft_strdup(champ_name)))
		ft_error("malloc failed in vm_fill_champion()", &vm_free_all);
	data->tab_champ[i]->num = n;
	vm_read_champ(champ_name, data->tab_champ[i]);
	return (0);
}

int		vm_isalready_set(int n, t_vm_data *data)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS && data->tab_champ[i])
	{
		if (data->tab_champ[i]->num == n)
			return (1);
		i++;
	}
	return (0);
}

int		get_next_player(t_vm_data *data)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!vm_isalready_set(i, data))
			return (i);
		i++;
	}
	return (i);
}
