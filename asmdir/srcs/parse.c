/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/03/29 09:22:12 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		set_error(int i, int nb_param, t_lx *elmt)
{
	if (i < nb_param)
		elmt->error = 2;
	else if (i >= nb_param)
		elmt->error = 4;
	return (1);
}

int		parse_instruction(t_list **list_lex, t_op *op)
{
	t_lx	*lx;
	int		i;
	size_t	line;

	lx = (*list_lex)->content;
	line = lx->pos[0];
	(*list_lex) = (*list_lex)->next;
	i = 0;
	while ((lx = (*list_lex)->content) && lx->pos[0] == line && !lx->error)
	{
		if (!arg_isvalid(op, i, list_lex) && (lx->error = 1))
			return (1);
		++i;
		if (!(*list_lex))
			break ;
		lx = (*list_lex)->content;
		if (i < op->nb_param && lx->word[0] == SEPARATOR_CHAR)
			(*list_lex) = (*list_lex)->next;
		else if (i < op->nb_param && lx->word[0] != SEPARATOR_CHAR)
			break ;
	}
	return ((i == op->nb_param) ? 0 : set_error(i, op->nb_param, lx));
}

int		parse_label(t_list *list_lex)
{
	t_lx	*lx;

	lx = list_lex->content;
	ft_printf("Parse label: %s\n", lx->word); // DEBUG A DELETE
	if (check_label_chars(lx->word, LABEL_CHARS))
		return (0);
	return (1);
}

void	parse_line(t_list **list_lex)
{
	t_op	*op;
	t_lx	*lx;

	lx = (*list_lex)->content;
	if (is_ref(lx, LABEL))
	{
		parse_label(*list_lex);
		if (is_ref(get_next_lx(*list_lex), LABEL)
			&& get_line(lx) == get_line(get_next_lx(*list_lex)))
			((t_lx*)((*list_lex)->content))->error = 16;
		*list_lex = get_next_lst((*list_lex));
	}
	if ((op = get_instruction((*list_lex)->content)))
		parse_instruction(list_lex, op);
	else
	{
		if (!op && ((t_lx*)((*list_lex)->content))->type == INSTRUCTION)
			((t_lx*)((*list_lex)->content))->error = 8;
		*list_lex = get_next_lst((*list_lex));
	}
}

void	parse(t_list *list_lex)
{
	check_name_and_cmt(&list_lex);
	while (list_lex)
	{
		parse_line(&list_lex);
	}
}
