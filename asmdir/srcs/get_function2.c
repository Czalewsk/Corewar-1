/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_function2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 16:05:38 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/16 16:08:17 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_lx	*get_lx_by_type(t_list *list_lex, int type)
{
	t_lx	*lx;

	if (!list_lex)
		return (NULL);
	while (list_lex)
	{
		lx = list_lex->content;
		if (lx->type == type)
			return (lx);
		list_lex = list_lex->next;
	}
	return (NULL);
}

char	get_arg_type(int type)
{
	if (type == REGISTRE)
		return (1);
	if (type == DIRECT)
		return (2);
	if (type == INDIRECT)
		return (4);
	if (type == LABELREF)
		return (2);
	return (0);
}

t_label	*get_label(t_list *list_label, t_lx *lx)
{
	t_label		*label;

	while (list_label)
	{
		label = list_label->content;
		if (!ft_strcmp(lx->word, label->name))
			return (label);
		list_label = list_label->next;
	}
	return (NULL);
}
