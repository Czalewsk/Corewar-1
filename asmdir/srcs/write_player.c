/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/03/29 11:20:28 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	set_codage(unsigned char *codage, t_lx *lx, int i)
{
	if (lx->type == REGISTRE)
		*codage = (*codage | (1 << (6 - i * 2)));
	else if (lx->type == DIRECT)
		*codage = (*codage | (2 << (6 - i * 2)));
	else if (lx->type == INDIRECT)
		*codage = (*codage | (3 << (6 - i * 2)));
}

t_buf	*param_to_buffer(size_t size, t_lx *lx, t_op *op, t_list *list_label)
{
	t_buf		*buffer_param;
	int			nb_octet;
	t_label		*label;

	buffer_param = (t_buf *)malloc(sizeof(t_buf));
	buffer_param->size = 0;
	buffer_param->data = NULL;
	nb_octet = 0;
	if (op->index && lx->type == DIRECT)
		nb_octet = 2;
	else if (lx->type == INDIRECT)
		nb_octet = 2;
	else if (lx->type == REGISTRE)
		nb_octet = 1;
	else if (lx->type == DIRECT)
		nb_octet = 4;
	if (lx->label)
	{
		label = get_label(list_label, lx);
		lx->valeur = label->octet - size;
	}
	write_bigendian(buffer_param, lx->valeur, nb_octet);
	ft_printf("Writing param %s: %d => %d octet\n", lx->word, lx->valeur, nb_octet);
	return (buffer_param);
}

void	write_instruction(t_buf *buffer, t_list **list_lex, t_op *op, t_list *list_label)
{
	int				i;
	t_buf			*buffer_param;
	unsigned char	codage;

	codage = 0;	
	i = 0;
	ft_printf("Writing instruction %s: %#04x\n", op->name, op->op_code);
	while (i < op->nb_param)
	{
		*list_lex = get_next_field(*list_lex);
		set_codage(&codage, (*list_lex)->content, i);
		buffer_param = param_to_buffer(buffer->size, (*list_lex)->content, op, list_label);
		++i;
	}
	// Write instruction to buffer
	write_to_buffer(buffer, &(op->op_code), 1);
	// Write codage to buffer
	if (op->octet_param)
	{
		write_to_buffer(buffer, &codage, 1);
		ft_printf("CODAGE %#04x\n", codage);
	}
	// Write (buffer)param to buffer
	write_to_buffer(buffer, buffer_param->data, buffer_param->size);
	ft_printf("size = %d\n", buffer_param->size);
}

void	write_line(t_buf *buffer, t_list **list_lex, t_list *list_label)
{
	t_op		*op;
	t_label		*label;

	if ((op = get_instruction((*list_lex)->content)))
	{
		write_instruction(buffer, list_lex, op, list_label);
	}
	else if (is_ref((*list_lex)->content, LABEL))
	{
		label = get_label(list_label, (*list_lex)->content);
		if (label->octet == -1)
			label->octet = buffer->size;
		ft_printf("LABEL DETECTED octet nb %d\n", buffer->size);
	}
}

void	write_player(t_buf *buffer, t_list *list_lex, t_list *list_label)
{
	ft_printf("Writing player started\n");
	t_list	*backup;

	backup = list_lex;
	while (list_lex && list_label)
	{
		write_line(buffer, &list_lex, list_label);
		list_lex = get_next_field(list_lex);
	}
	list_lex = backup;
	buffer->size = 0;
	buffer->data = NULL;
	while (list_lex)
	{
		write_line(buffer, &list_lex, list_label);
		list_lex = get_next_field(list_lex);
	}
	ft_printf("Writing player finished\n");
}
