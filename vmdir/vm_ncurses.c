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

void	vm_ncurses_init(t_vm_data *data, t_ncurses_data *ncurses_data)
{
	(void)data;
	(void)ncurses_data;
	ncurses_data->w = initscr();
	ncurses_data->interval = 1;
	ncurses_data->data = data;
	start_color();
	noecho();
	cbreak();
	nodelay(ncurses_data->w, TRUE);
	keypad(ncurses_data->w, TRUE);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(128, COLOR_WHITE, COLOR_RED); 
}

void	vm_ncurses_free(void)
{
	endwin();
}


void	curses_get_key(t_ncurses_data *ncurses_data)
{
	int		ch;

	ch = getch();
	if (ch == KEY_UP)
		ncurses_data->interval += 100;
	else if (ch == KEY_DOWN && ncurses_data->interval > 100)
		ncurses_data->interval -= 100;
	else if (ch == ' ')
		curses_print_process(ncurses_data);
}

void	vm_ncurses(t_ncurses_data *ncurses_data)
{
	erase();
	curses_print_arena(ncurses_data->data);
	curses_print_globad_info(ncurses_data);
	mvprintw(64 + 1, 1, "Press space to pause the program and see processes");
	curses_get_key(ncurses_data);
	refresh();
}