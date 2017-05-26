/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:06:07 by lduval            #+#    #+#             */
/*   Updated: 2017/05/26 13:14:42 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_HEADER_H
# define VM_HEADER_H
# include <stdlib.h>
# include <stdio.h>
# include <ncurses.h>
# include "../libft/libft.h"
# include "op.h"

# define VM_OPT_G 1
# define VM_OPT_V 2
# define VM_OPT_S 4

typedef struct		s_buf
{
	void			*data;
	size_t			size;
}					t_buf;

typedef struct		s_vm_proc
{
	unsigned char	registre[REG_SIZE * (REG_NUMBER + 1)];
	int				pc;
	int				carry;
	int				champ;
	int				last_live;
	int				in_proc;
	char			next_op;
	int				progsize;
	unsigned int	ocp;
	int				color;
	int				nproc;
}					t_vm_proc;

typedef struct		s_vm_champ
{
	char			*name;
	t_header		header;
	int				num;
	unsigned char	*prog;
	int				posnum;
}					t_vm_champ;

typedef struct		s_vm_data
{
	int				nbr_cycle;
	int				nbr_lives;
	int				cycletodie;
	int				lastcycledec;
	int				lastcheck;
	unsigned int	option;
	int				dump;
	t_vm_champ		*tab_champ[MAX_PLAYERS + 1];
	unsigned char	arena[MEM_SIZE];
	unsigned char	col_arena[MEM_SIZE];
	t_list			*tab_proc;
	int				nb_proc;
	int				winner;
	unsigned char	affchar;
	pid_t			sound_process;
}					t_vm_data;

typedef struct		s_op
{
	char			*name;
	int				nb_p;
	int				type_param[3];
	int				op_code;
	int				nb_cycle;
	char			*cmt;
	int				octet;
	int				index;
}					t_op;

typedef struct		s_ncurses_data
{
	WINDOW			*w;
	int				interval;
	t_vm_data		*data;
}					t_ncurses_data;

t_vm_data			*get_data();
void				vm_free_all();
void				vm_print_arena(void);

void				vm_fight(void);
void				vm_init_arena();
int					vm_pars_param(int nb_parm, char **tab_parm);
void				vm_read_champ(char *champ_name, t_vm_champ *data);

void				vm_ncurses(t_ncurses_data *ncurses_data);
void				vm_ncurses_init(t_vm_data *data,
		t_ncurses_data *ncurses_data);
void				vm_ncurses_free(void);
void				curses_print_globad_info(t_ncurses_data *ncurses_data,
		WINDOW *border);
void				curses_print_arena(t_vm_data *data);
void				curses_print_process(t_ncurses_data *ncurses_data);
void				vm_adv_verb(t_vm_proc *proc, int *nb_octet);
void				ft_say(char *input);
void				ft_afplay(char *input);
void				del_tab_proc(void *content, size_t size);
void				vm_exec_op(t_vm_data *data, t_vm_proc *proc);
int		vm_fill_champion(char *champ_name, int n, t_vm_data *data);
int		vm_isalready_set(int n, t_vm_data *data);
int		get_next_player(t_vm_data *data);
#endif
