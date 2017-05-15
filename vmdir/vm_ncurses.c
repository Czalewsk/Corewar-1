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

void	curse_print_player_info(t_vm_champ **tab_champ, int column, int i)
{
	int		c;

	c = 0;
	while (tab_champ[c])
	{
		attron(COLOR_PAIR((ft_power(2, c))));
		mvprintw((i = i + 2), column + 2, "Player name: %s (%d)", tab_champ[c]->name, tab_champ[c]->num);
		mvprintw((i = i + 2), column + 2, "Alive: %d", tab_champ[c]->isalive);
		attroff(COLOR_PAIR((ft_power(2, c))));
		++i;
		++c;
	}
}

void	curse_print_globad_info(t_vm_data *data)
{
	WINDOW		*border;
	int			i;
	int			column;

	i = 3;
	column = (MEM_SIZE / 64) * 3;
	border = subwin(stdscr, LINES,  COLS - column, 0, column);
	wborder(border, '|', '|', '-', '-', '/', '\\', '\\', '/');
	attron(A_BOLD);
	mvprintw(1, column + ((COLS - column) / 2) - (ft_strlen("CLX Virtual Machine") / 2), "CLX Virtual Machine");
	attroff(A_BOLD);
	mvprintw((i = i + 2), column + 2, "dump: %d", data->dump);
	mvprintw((i = i + 2), column + 2, "nbr_cycle: %d", data->nbr_cycle);
	mvprintw((i = i + 2), column + 2, "cycletodie: %d", data->cycletodie);
	mvprintw((i = i + 2), column + 2, "nb_proc: %d", data->nb_proc);
	mvprintw((i = i + 2), column + 2, "winner: %s", data->winner);
	curse_print_player_info(data->tab_champ, column, i + 2);
	attron(A_DIM);
	mvprintw(LINES - 2, column + 2, "Pls give us 250/118");
	attroff(A_DIM);
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
			if ((data->col_arena[i] & 0xf) == 0)
					attron(A_DIM);
			if ((data->col_arena[i] & 128))
				attron(COLOR_PAIR(128));
			else
				attron(COLOR_PAIR((data->col_arena[i] & 0xf)));
			mvprintw(y, x * 3, "%.2x ", data->arena[i]);
			if ((data->col_arena[i] & 128))
				attroff(COLOR_PAIR(128));
			else
				attroff(COLOR_PAIR((data->col_arena[i] & 0xf)));
			if ((data->col_arena[i] & 0xf) == 0)
					attroff(A_DIM);
			++y;
			++i;
		}
		++x;
	}
}

void	curse_print_process(t_list *list_proc)
{
	static	t_vm_proc	*proc = NULL;
	int					reg;
	int					i;
	
	if (!proc)
		proc = list_proc->content;
	mvprintw(64 + 1, 1, "PC: %d, Carry: %d, Next op: %.2x (%d)",
	proc->pc, proc->carry, proc->next_op, proc->champ);
	i = 0;
	while (i < REG_NUMBER)
	{
		ft_memcpy(&reg, proc->registre + (REG_SIZE * i), REG_SIZE);
		mvprintw(64 + 3, 3 + (i * 11), "%d", reg);
		i++;
	}
}

void	vm_ncurses(void /*WINDOW *w*/)
{
	t_vm_data	*data;
	cbreak();
	getch();
//	nodelay(w, TRUE);
	data = get_data();
	clear();
	curse_print_arena(data);
	curse_print_globad_info(data);
	curse_print_process(data->tab_proc);
	refresh();
}