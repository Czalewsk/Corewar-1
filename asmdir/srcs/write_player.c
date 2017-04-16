/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/04/17 01:13:05 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_instruction(t_buf *buffer, t_list **list_lex, t_op *op,
		t_list *list_label)
{
	int				i;
	t_buf			buffer_param;
	unsigned char	codage;

	codage = 0;
	i = 0;
	buffer_param.data = NULL;
	buffer_param.size = 0;
	ft_printf("Writing instruction %s: %#04x\n", op->name, op->op_code);
	write_to_buffer(buffer, &(op->op_code), 1);
	set_codage(&codage, *list_lex, op);
	if (op->octet)
	{
		write_to_buffer(buffer, &codage, 1);
		ft_printf("CODAGE %#04x\n", codage);
	}
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
		ft_printf("LABEL DETECTED octet nb %d\n", buffer->size);
	}
}

void	write_player(t_buf *buffer, t_list *list_lex, t_list *list_label,
		header_t *header)
{
	t_list	*backup;

	ft_printf("Writing player started\n");
	backup = list_lex;
	while (list_lex && list_label)
	{
		write_line(buffer, &list_lex, list_label);
		list_lex = get_next_field(list_lex);
	}
	list_lex = backup;
	fill_header(header, list_lex, buffer);
	buffer->size = 0;
	buffer->data = NULL;
	while (list_lex)
	{
		write_line(buffer, &list_lex, list_label);
		list_lex = get_next_field(list_lex);
	}
	ft_printf("Writing player finished\n");
}
