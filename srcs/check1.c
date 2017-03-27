/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 16:44:31 by xesnault          #+#    #+#             */
/*   Updated: 2017/03/27 16:44:33 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

int		is_instruction(char *instruction)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strcmp(instruction, g_op_tab[i].name))
			return (1);
		++i;
	}
	return (0);
}

int		is_ref(t_lx *lx, int ref)
{
	if (!lx)
		return (0);
	if (lx->type == ref)
		return (1);
	return (0);
}
