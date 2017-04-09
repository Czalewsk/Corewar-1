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

void	set_codage(unsigned char *codage, t_list *list_lex, t_op *op)
{
	int		i;
	t_lx	*lx;

	i = 0;
	while (i < op->nb_param)
	{
		list_lex = get_next_field(list_lex);
		lx = list_lex->content;
		if (lx->type == REGISTRE)
			*codage = (*codage | (1 << (6 - i * 2)));
		else if (lx->type == DIRECT)
			*codage = (*codage | (2 << (6 - i * 2)));
		else if (lx->type == INDIRECT)
			*codage = (*codage | (3 << (6 - i * 2)));
		++i;
	}
	
}
void	param_to_buffer(t_buf *buffer, t_list **list_lex, t_op *op, t_list *list_label)
{
	int			nb_octet;
	t_label		*label;
	t_buf 		buffer_param;
	t_lx 		*lx;
	int    		i;

	i = 0;
	buffer_param.data = NULL;
	buffer_param.size = 0;
	while (i < op->nb_param)
	{
		nb_octet = 0;
		*list_lex = get_next_field(*list_lex);
		lx = (*list_lex)->content;
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
			lx->valeur = label->octet - (buffer->size - 1 - (op->index ? 0 : 1));
		}
		write_bigendian(&buffer_param, lx->valeur, nb_octet);
		ft_printf("Writing param %s: %d => %d octet\n", lx->word, lx->valeur, nb_octet);
		++i;
	}
	// Write (buffer)param to buffer
	write_to_buffer(buffer, buffer_param.data, buffer_param.size);
	ft_printf("size = %d\n", buffer_param.size);
}

void	write_instruction(t_buf *buffer, t_list **list_lex, t_op *op, t_list *list_label)
{
	int				i;
	t_buf			buffer_param;
	unsigned char	codage;

	codage = 0;	
	i = 0;
	buffer_param.data = NULL;
	buffer_param.size = 0;
	ft_printf("Writing instruction %s: %#04x\n", op->name, op->op_code);
	// Write instruction to buffer
	write_to_buffer(buffer, &(op->op_code), 1);
	set_codage(&codage, *list_lex, op);
	// Write codage to buffer
	if (op->octet_param)
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
