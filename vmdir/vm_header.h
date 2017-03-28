/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:06:07 by lduval            #+#    #+#             */
/*   Updated: 2017/03/28 04:44:45 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VM_HEADER_H
# define VM_HEADER_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct	s_vm_data
{
	int dump;
}				t_vm_data;

t_vm_data		*get_data();
void			vm_free_all();
int				vm_pars_param(int nb_parm, char **tab_parm);

#endif
