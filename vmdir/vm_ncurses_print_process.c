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

static void	curses_print_process_reg(t_vm_proc *proc)
{
	int		i;
	int		reg;

	i = 0;
	while (i < REG_NUMBER)
	{
		ft_memcpy(&reg, proc->registre + (REG_SIZE * i), REG_SIZE);
		mvprintw(64 + 3, 3 + (i * 11), "%d", reg);
		i++;
	}
}

static int	curses_print_process_gk(int *key_space, int *cursor_proc,
			t_list **list_proc, t_ncurses_data *ncurses_data)
{
	int				ch;

	ch = getch();
	if (ch != ' ')
		*key_space = 0;
	else if (ch == ' ' && !*key_space)
		return (1);
	if (ch == KEY_RIGHT && (*list_proc)->next)
	{
		*list_proc = (*list_proc)->next;
		++(*cursor_proc);
	}
	else if (ch == KEY_RIGHT && !(*list_proc)->next)
	{
		*list_proc = ncurses_data->data->tab_proc;
		*cursor_proc = 1;
	}
	else if (ch == KEY_LEFT)
	{
		*list_proc = ncurses_data->data->tab_proc;
		*cursor_proc = 1;
	}
	return (0);
}

void		curses_print_process(t_ncurses_data *ncurses_data)
{
	int				key_space;
	
	t_list			*list_proc;
	t_vm_proc		*proc;
	int				cursor_proc;

	cursor_proc = 1;
	key_space = 1;
	list_proc = ncurses_data->data->tab_proc;
	while (true)
	{
		erase();
		curses_print_arena(ncurses_data->data);
		curses_print_globad_info(ncurses_data);	
		proc = list_proc->content;
		mvprintw(64 + 1, 1, "PC: %-4d, Carry: %d, Next op: %.2x (%d) [%d/%d]",
		proc->pc, proc->carry, proc->next_op, proc->champ, cursor_proc,
		ft_lstlen(ncurses_data->data->tab_proc));
		curses_print_process_reg(proc);
		refresh();
		if (curses_print_process_gk(&key_space, &cursor_proc, &list_proc, ncurses_data))
			break ;
	}
}
