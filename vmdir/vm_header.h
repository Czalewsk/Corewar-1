/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:06:07 by lduval            #+#    #+#             */
/*   Updated: 2017/04/01 14:42:31 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VM_HEADER_H
# define VM_HEADER_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../asmdir/includes/op.h"

typedef struct  s_vm_reg
{

}               t_vm_reg;

typedef struct	s_vm_champ
{
	char	registre[REG_NUMBER * REG_SIZE];
	char	pc[REG_SIZE];
	int     carry;
	int     num;
	char	*name;

}		t_vm_champ;

typedef struct			s_vm_data
{
	int 		dump;
	t_vm_champ	*tab_champ[MAX_PLAYERS];
	t_vm_reg    arena[MEM_SIZE];
}				t_vm_data;

t_vm_data		*get_data();
void			vm_free_all();

int				vm_pars_param(int nb_parm, char **tab_parm);
void            vm_read_champ(char *champ_name,t_vm_champ *data);

#endif
