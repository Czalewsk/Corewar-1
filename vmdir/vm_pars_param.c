/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:03:10 by lduval            #+#    #+#             */
/*   Updated: 2017/03/28 04:43:14 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

static int vm_fill_champion(char *tab_param[*i], int n)
{
	return 0;
}

static void vm_pars_champions(int nb_param, char **tab_param, int *i, t_vm_data *data)
{
	int				n_next_player;
	unsigned int	n_free;
	char			*t;
	int				finish;

	n_free = 0;
	finish = 0;
	t = NULL;
	while (*i < nb_param && !finish)
	{
		if (ft_strequ("-n", tab_param[*i]))
		{
			if (*i + 2 >= nb_param ||!ft_strisnumber(tab_param[*i + 1])
			 || ((n_next_player = ft_atoi(tab_param[*i + 1])) < 0)
			 ||  !(t = ft_strrstr(".cor", tab_param[*i])) || !*(t + 4))
				ft_error("-n wrong input", &vm_free_all);
			*i += 2;
		}
		else
			n_next_player = n_free;
		finish += ((t = ft_strrstr(".cor", tab_param[*i])) && *(t + 4)) ?
			vm_fill_champion(tab_param[*i], n_next_player) : 1;
		(*i)++;
	}
}

static void vm_pars_option(int nb_param, char **tab_param, int i, t_vm_data *data)
{
	return ;
	while (i < nb_param)
	{
				
	}
}

static void vm_pars_dump(char **tab_param, t_vm_data *data)
{
	int dump;

	dump = 0;
	if (ft_strequ(tab_param[0], "-dump"))
		ft_error("first parametre must be '-dump'", &vm_free_all);
	if (!ft_strisnumber(tab_param[1]))
		ft_error("second parametre must be a number", &vm_free_all);
	if ((dump = ft_atoi(tab_param[1]) <= 0))
		ft_error("second parametre must be positive", &vm_free_all);
	data->dump = dump;
}

/*
** [pars_param()]
** Verifie si la machine est lancée de la bonne manière
** soit de la manière suivante 
** ./corewar [-dump nbr_cycles] [[-n number] champion.cor] ...[-g]
*/

int	vm_pars_param(int nb_param, char **tab_param)
{
	int error;
	t_vm_data *data;
	int i;

	error = 0;
	i = 3;
	data = get_data();
	if (nb_param < 4)
		ft_error("not enought parametre", &vm_free_all);
	vm_pars_dump(tab_param, data);
	vm_pars_champions(nb_param, tab_param, &i, data);
	vm_pars_option(nb_param, tab_param, i, data);
	return (error);
}
