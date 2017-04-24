/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:06:07 by lduval            #+#    #+#             */
/*   Updated: 2017/04/19 04:41:26 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VM_HEADER_H
# define VM_HEADER_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "op.h"

typedef struct      s_buf
{
	void            *data;
	size_t          size;
}					t_buf;

typedef struct	s_vm_proc
{
	char		registre[REG_NUMBER * REG_SIZE + 1];
	int			pc;
	int			carry;
	int			champ;
	int			beg;
	int			last_live;
}				t_vm_proc;

typedef struct	s_vm_champ
{
	int			isalive;
	char		*name;
	header_t	header;
	int			num;
	unsigned char *prog;
}				t_vm_champ;


typedef struct			s_vm_data
{
	int 		dump;
	t_vm_champ	*tab_champ[MAX_PLAYERS + 1];
	char		*arena[MEM_SIZE];
	t_vm_proc   *tab_proc;
	int         nb_proc;
}				t_vm_data;

t_vm_data		*get_data();
void			vm_free_all();
void vm_print_arena(void);

int				vm_pars_param(int nb_parm, char **tab_parm);
void            vm_read_champ(char *champ_name,t_vm_champ *data);

#endif
