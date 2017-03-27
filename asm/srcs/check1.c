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

t_op	*get_instruction(char *instruction)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (!ft_strcmp(instruction, g_op_tab[i].name))
			return (g_op_tab + i);
		++i;
	}
	return (NULL);
}

int		is_ref(t_lx *lx, int ref)
{
	if (!lx || lx->type != ref)
		return (0);
	return (1);
}

int		get_line(t_lx *lx)
{
	if (!lx)
		return (0);
	return (lx->pos[0]);
}

t_lx	*get_next_lx(t_list *list_lex)
{
	if (!list_lex)
		return (NULL);
	list_lex = list_lex->next;
	while (list_lex)
	{
		if (!is_ref(list_lex->content, SEPARATEUR))
			return (list_lex->content);
		list_lex = list_lex->next;
	}
	return (NULL);
}
