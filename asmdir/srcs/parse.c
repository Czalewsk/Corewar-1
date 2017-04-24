/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/04/24 08:11:43 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			set_error(int i, int nb_param, t_lx *elmt, int value)
{
	if (value)
	{
		elmt->error = value;
		return (1);
	}
	if (i < nb_param)
		elmt->error = 2;
	return (1);
}

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
	while (curs && (lx = curs->content) && line == lx->pos[0])
	{
		if (*lx->word == SEPARATOR_CHAR && !sep)
		{
			last_sep = lx;
			sep = 1;
		}
		else if (*lx->word == SEPARATOR_CHAR && sep && (lx->error = 16))
			return (0); // Expected statement
		else
			sep = 0;
		curs = curs->next;
	}
	sep ? last_sep->error = 17 : 0;
	return (1);
}

int			parse_instruction(t_list **list_lex, t_op *op, t_list *label)
{
	size_t	line;
	t_lx	*lx;
	int		nb_p;

	lx = (*list_lex)->content;
	line = lx->pos[0];
	if (!check_sep(*list_lex, lx))
	{
		*list_lex = get_next_lst((*list_lex));
		return (0);
	}
	if ((nb_p = count_param((*list_lex)->next, lx, line)) != op->nb_p)
	{
		lx->error = 7;
		//Set dans la struct le nbr de param attendu
		*list_lex = get_next_lst((*list_lex));
		return (0);
	}
	if (!arg_isvalid(list_lex, lx, op, label))
	{
		lx->error = 6;
		return (0);
	}
	return (1);
}

int			parse_label(t_lx *lx, t_list *lst_lbl)
{
	t_label		*lbl;

	while (lst_lbl)
	{
		lbl = lst_lbl->content;
		if (!ft_strcmp(lbl->name, lx->word))
			return (1);
		lst_lbl = lst_lbl->next;
	}
	lx->error = 2;
	return (0);
}

void		parse_line(t_list **list_lex, t_list *label)
{
	t_op	*op;
	t_lx	*lx;

	lx = (*list_lex)->content;
	if (lx->type == LABEL)
	{
		parse_label(lx, label);
		if (is_ref(get_next_lx(*list_lex), LABEL)
				&& get_line(lx) == get_line(get_next_lx(*list_lex)))
			((t_lx*)((*list_lex)->content))->error = 16;
		*list_lex = get_next_lst((*list_lex));
	}
	if ((op = get_instruction((*list_lex)->content)))
		parse_instruction(list_lex, op, label);
	else
	{
		if (lx->type == SEPARATEUR)
			lx->error = 1; // Separateur au debut de ligne
		else if (!op && ((t_lx*)((*list_lex)->content))->type == INSTRUCTION)
			((t_lx*)((*list_lex)->content))->error = 8;
		*list_lex = get_next_lst((*list_lex));
	}
}

void		parse(t_list *list_lex, t_list *label, header_t *header)
{
	check_name_and_cmt(&list_lex, header);
	check_label_chars(label);
	while (list_lex)
	{
		parse_line(&list_lex, label);
	}
}
