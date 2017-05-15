/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:06:07 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 10:03:06 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_HEADER_H
# define VM_HEADER_H
# include <stdlib.h>
# include <stdio.h>
# include <ncurses.h>
# include "../libft/libft.h"
# include "op.h"
//# include "vm_op/vm_op.h"
# define VM_OPT_G 1

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
	unsigned char	*prog;
	int				progsize;
	unsigned int			ocp;
	int				color;
}					t_vm_proc;

typedef struct		s_vm_champ
{
	char			*name;
	t_header		header;
	int				num;
	unsigned char	*prog;
}					t_vm_champ;

typedef struct		s_vm_data
{
	int				nbr_cycle;
	int				nbr_lives;
	int				cycletodie;
	int				lastcycledec;
	unsigned int	option;
	int				dump;
	t_vm_champ		*tab_champ[MAX_PLAYERS + 1];
	unsigned char	arena[MEM_SIZE];
	unsigned char	col_arena[MEM_SIZE];
	t_list			*tab_proc;
	int				nb_proc;
	char			*winner;
}					t_vm_data;

typedef struct	s_op
{
	char		*name;
	int			nb_p;
	int			type_param[3];
	int			op_code;
	int			nb_cycle;
	char		*cmt;
	int			octet;
	int			index;
}				t_op;

t_vm_data			*get_data();
void				vm_free_all();
void				vm_print_arena(void);

void				vm_fight(void);
void				vm_init_arena();
int					vm_pars_param(int nb_parm, char **tab_parm);
void				vm_read_champ(char *champ_name, t_vm_champ *data);

void				vm_ncurses(void);

//void     (*g_vm_exec_op[17])(t_vm_data *,t_vm_proc *,int );

#endif
