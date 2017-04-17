/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_function1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 16:07:22 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/16 18:29:18 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

t_op	*get_instruction(t_lx *lx)
{
	int		i;

	i = 0;
	if (lx->type != INSTRUCTION)
		return (0);
	while ((g_op_tab[i]).name)
	{
		if (!ft_strcmp(lx->word, g_op_tab[i].name))
			return (g_op_tab + i);
		++i;
	}
	return (NULL);
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

t_list	*get_next_lst(t_list *list_lex)
{
	if (!list_lex)
		return (NULL);
	list_lex = list_lex->next;
	while (list_lex)
	{
		if (!is_ref(list_lex->content, SEPARATEUR))
			return (list_lex);
		list_lex = list_lex->next;
	}
	return (NULL);
}

t_list	*get_next_field(t_list *list_lex)
{
	if (!list_lex)
		return (NULL);
	list_lex = list_lex->next;
	while (list_lex)
	{
		if (!is_ref(list_lex->content, SEPARATEUR)
				&& !is_ref(list_lex->content, DIRECTCHAR))
			return (list_lex);
		list_lex = list_lex->next;
	}
	return (NULL);
}
