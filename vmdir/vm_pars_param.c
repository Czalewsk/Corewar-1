/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:03:10 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 11:27:22 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

static int		vm_fill_champion(char *champ_name, int n, t_vm_data *data)
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

static int		vm_isalready_set(int n, t_vm_data *data)
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

static int		get_next_player(t_vm_data *data)
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

static void		vm_pars_champions_extand(int *finish, char **t)
{
	*finish = 0;
	*t = NULL;
}

static void		vm_pars_champions(int nb_param, char **tab_param, int *i, t_vm_data *data)
{
	int				n_next_player;
	char			*t;
	int				finish;

	vm_pars_champions_extand(&finish, &t);
	while (*i < nb_param && !finish)
	{
		if (ft_strequ("-n", tab_param[*i]))
		{
			if ((*i) + 2 >= nb_param || !ft_isint(tab_param[*i + 1])
					|| !((n_next_player = ft_atoi(tab_param[*i + 1])) || 1) ||
					vm_isalready_set(n_next_player, data)
					|| !(t = ft_strrstr(tab_param[*i + 2], ".cor")) || (*(t + 4)))
				ft_error("-n wrong input", &vm_free_all);
			*i += 2;
		}
		else
			n_next_player = get_next_player(data);
		finish += ((t = ft_strrstr(tab_param[*i], ".cor")) && !(*(t + 4))) ?
			vm_fill_champion(tab_param[*i], n_next_player, data) : 1;
		(*i) += finish ? 0 : 1;
	}
}

static void		vm_pars_option(int nb_param, char **tab_param, int i, t_vm_data *data)
{
	while (i < nb_param)
	{
		if (ft_strequ(tab_param[i], "-g"))
			data->option |= 1;
		else if (ft_strequ(tab_param[i], "-v"))
			data->option = 2;
		else if (ft_strequ(tab_param[i], "-s"))
			data->option |= 4;
		else
		{
			ft_printf("%s ", tab_param[i]);
			ft_error("illegal option, or already set", &vm_free_all);
		}
		i++;
	}
}

static void		vm_pars_dump(char **tab_param, t_vm_data *data, 
		int nb_param, int *i)
{
	int dump;

	dump = -1;
	if (ft_strequ(tab_param[1], "-dump"))
	{
		if (nb_param < 4)
			ft_error("not enought parameter", &vm_free_all);
		if (!ft_strisnumber(tab_param[2]))
			ft_error("second parameter must be a number", &vm_free_all);
		if ((dump = ft_atoi(tab_param[2])) <= 0)
			ft_error("second parameter must be positive", &vm_free_all);
		*i = 3;
	}
	data->dump = dump;
}

int				vm_pars_param(int nb_param, char **tab_param)
{
	int			error;
	t_vm_data	*data;
	int			i;

	error = 0;
	i = 1;
	data = get_data();
	vm_pars_dump(tab_param, data,nb_param, &i);
	vm_pars_champions(nb_param, tab_param, &i, data);
	vm_pars_option(nb_param, tab_param, i, data);
	return (error);
}
