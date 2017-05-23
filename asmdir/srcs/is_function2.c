/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 15:55:33 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/23 09:40:45 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

int		is_instruction(t_lx *lx)
{
	int		i;

	i = 0;
	while ((g_op_tab[i]).name)
	{
		if (!ft_strcmp(lx->word, g_op_tab[i].name))
			return (1);
		++i;
	}
	return (0);
}
