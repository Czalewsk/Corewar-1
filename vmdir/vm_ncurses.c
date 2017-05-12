/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 22:48:45 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 03:24:11 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

void	curse_print_globad_info(t_vm_data *data)
{
	int		i;
	int		column;

	i = 3;
	column = 5 + (MEM_SIZE / 64) * 3;
	mvprintw((i = i + 2), column, "nbr_cycle: %d", data->nbr_cycle);
	mvprintw((i = i + 2), column, "cycletodie: %d", data->cycletodie);
	mvprintw((i = i + 2), column, "nb_proc: %d", data->nb_proc);
	mvprintw((i = i + 2), column, "winner: %s", data->winner);
}

void	curse_print_arena(t_vm_data *data)
{
	int		x;
	int		y;
	int		i;

	x = 0;
	i = 0;
	while (x < COLS / 3 && i < MEM_SIZE)
	{
		y = 0;
		while (y < 64 && i < MEM_SIZE)
		{
			if ((data->col_arena[i] & 128))
				attron(COLOR_PAIR(128));
			else
				attron(COLOR_PAIR((data->col_arena[i] & 0xf)));
			mvprintw(y, x * 3, "%.2x ", data->arena[i]);
			if ((data->col_arena[i] & 128))
				attroff(COLOR_PAIR(128));
			else
				attroff(COLOR_PAIR((data->col_arena[i] & 0xf)));
			++y;
			++i;
		}
		++x;
	}
}

void	vm_ncurses(void)
{
	t_vm_data	*data;

	data = get_data();
	curse_print_arena(data);
	curse_print_globad_info(data);
	refresh();			/* Print it on to the real screen */
}