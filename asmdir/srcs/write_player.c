/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/04/17 12:47:27 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_instruction(t_buf *buffer, t_list **list_lex, t_op *op,
		t_list *list_label)
{
	unsigned char	codage;

	codage = 0;
	write_to_buffer(buffer, &(op->op_code), 1);
	ft_printf("size is %d\n", buffer->size);
	set_codage(&codage, *list_lex, op);
	if (op->octet)
		write_to_buffer(buffer, &codage, 1);
	param_to_buffer(buffer, list_lex, op, list_label);
}

void	write_line(t_buf *buffer, t_list **list_lex, t_list *list_label)
{
	t_op		*op;
	t_label		*label;

	if ((op = get_instruction((*list_lex)->content)))
		write_instruction(buffer, list_lex, op, list_label);
	else if (is_ref((*list_lex)->content, LABEL))
	{
		label = get_label(list_label, (*list_lex)->content);
		if (label->octet == -1)
			label->octet = buffer->size;
	}
}

void	write_player(t_buf *buffer, t_list *list_lex, t_list *list_label,
		header_t *header)
{
	t_list	*backup;

	backup = list_lex;
	while (list_lex)
	{
		write_line(buffer, &list_lex, list_label);
		list_lex = get_next_field(list_lex);
	}
	list_lex = backup;
	fill_header(header, list_lex, buffer);
	ft_memdel((void**)&buffer->data);
	buffer->size = 0;
	while (list_lex)
	{
		write_line(buffer, &list_lex, list_label);
		list_lex = get_next_field(list_lex);
	}
}
