/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/04/23 14:28:46 by czalewsk         ###   ########.fr       */
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

int			parse_instruction(t_list **list_lex, t_op *op, t_list *label)
{
	t_lx	*lx;
	int		i;
	size_t	line;
	t_lx	*h_lx;

	lx = (*list_lex)->content;
	h_lx = lx;
	line = lx->pos[0];
	(*list_lex) = (*list_lex)->next;
	i = 0;
	while (*list_lex && (lx = (*list_lex)->content)
			&& lx->pos[0] == line && !lx->error)
	{
		if ((h_lx->error = arg_isvalid(op, i, list_lex, label)))
			return (1);
		++i;
		if (!(*list_lex))
			break ;
		lx = (*list_lex)->content;
		if (lx->word[0] != SEPARATOR_CHAR && lx->pos[0] == line)
			return (set_error(i, op->nb_p, h_lx, 1));
		if (i < op->nb_p && lx->word[0] == SEPARATOR_CHAR && (*list_lex)->next)
			(*list_lex) = (*list_lex)->next;
	}
	return ((i == op->nb_p || lx->error) ? 0 : set_error(i, op->nb_p, h_lx, 0));
}

void		parse_label(t_lx *lx, t_list *lst_lbl)
{
	t_label		*lbl;

	while (lst_lbl)
	{
		lbl = lst_lbl->content;
		if (!ft_strcmp(lbl->name, lx->word))
			return ;
		lst_lbl = lst_lbl->next;
	}
	lx->error = 2;
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
		if (!op && ((t_lx*)((*list_lex)->content))->type == INSTRUCTION)
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
