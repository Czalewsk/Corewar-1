/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 19:41:14 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/25 19:41:45 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			count_param(t_list *lst, t_lx *lx, size_t line)
{
	int		i;

	i = 0;
	if (!lst)
		return (0);
	while (lst && (lx = lst->content) && line == lx->pos[0])
	{
		if (*((t_lx*)lst->content)->word == SEPARATOR_CHAR && lst->next)
			lst = lst->next;
		lx = lst->content;
		if ((lx->type == DIRECTCHAR || *lx->word == LABEL_CHAR) && lst->next)
		{
			lst = lst->next;
			lx = lst->content;
		}
		lst = lst->next;
		if (lx->pos[0] != line)
			break ;
		i++;
	}
	return (i);
}

int			check_sep(t_list *curs, t_lx *lx)
{
	size_t		line;
	int			sep;
	t_lx		*last_sep;

	sep = 0;
	line = lx->pos[0];
	if (((t_lx *)curs->content)->word[0] == SEPARATOR_CHAR && (lx->error = 16))
		return (0);
	while (curs && (lx = curs->content) && line == lx->pos[0])
	{
		if (*lx->word == SEPARATOR_CHAR && !sep && (sep = 1))
			last_sep = lx;
		else if (*lx->word == SEPARATOR_CHAR && sep && (lx->error = 16))
			return (0);
		else if (!(sep = 0) && (lx->type == DIRECTCHAR
					|| *lx->word == LABEL_CHAR) && curs->next)
			curs = curs->next;
		curs = curs->next;
		if (curs && ((t_lx *)curs->content)->pos[0] == line && !sep &&
		((t_lx *)curs->content)->word[0] != SEPARATOR_CHAR && (lx->error = 18))
			return (0);
	}
	sep ? last_sep->error = 17 : 0;
	return (1);
}
