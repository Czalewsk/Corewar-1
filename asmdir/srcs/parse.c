/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/05/23 09:36:59 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			parse_instruction(t_list **list_lex, t_op *op, t_list *label)
{
	size_t	line;
	t_lx	*lx;
	int		nb_p;

	lx = (*list_lex)->content;
	line = lx->pos[0];
	if (!check_sep((*list_lex)->next, lx))
	{
		*list_lex = get_next_lst((*list_lex));
		return (0);
	}
	if ((nb_p = count_param((*list_lex)->next, lx, line)) != op->nb_p)
	{
		lx->error = 7;
		lx->param_error = nb_p;
		*list_lex = get_next_lst((*list_lex));
		return (0);
	}
	if ((lx->param_error = arg_isvalid(list_lex, lx, op, label)) != -1)
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
			((t_lx*)((*list_lex)->content))->error = 23;
		*list_lex = get_next_lst((*list_lex));
	}
	if ((*list_lex) && (op = get_instruction((*list_lex)->content)))
		parse_instruction(list_lex, op, label);
	else if (*list_lex)
	{
		if (lx->type == SEPARATEUR)
			lx->error = 1;
		else if (!op && ((t_lx*)((*list_lex)->content))->type == INSTRUCTION)
			((t_lx*)((*list_lex)->content))->error = 20;
		*list_lex = get_next_lst((*list_lex));
	}
}

void		parse(t_list *list_lex, t_list *label, header_t *header)
{
	check_name(&list_lex, header);
	check_comment(&list_lex, header);
	check_label_chars(label);
	while (list_lex)
		parse_line(&list_lex, label);
}
