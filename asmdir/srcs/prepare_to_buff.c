/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_buff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:53:05 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/22 19:51:30 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	fill_header(header_t *header, t_list *list_lex, t_buf *buffer)
{
	(void)list_lex;
	header->magic = COREWAR_EXEC_MAGIC;
	header->prog_size = buffer->size;
}

void	param_to_buffer(t_buf *buffer, t_list **list_lex,
			t_op *op, t_list *list_label)
{
	int			nb_octet;
	t_label		*label;
	t_buf		buffer_param;
	t_lx		*lx;
	int			i;

	i = -1;
	buffer_param.data = NULL;
	buffer_param.size = 0;
	while (++i < op->nb_p && !(nb_octet = 0))
	{
		*list_lex = get_next_field(*list_lex);
		lx = (*list_lex)->content;
		if ((op->index && lx->type == DIRECT) || lx->type == INDIRECT)
			nb_octet = 2;
		else if (lx->type == REGISTRE)
			nb_octet = 1;
		else if (lx->type == DIRECT)
			nb_octet = 4;
		if (lx->label && (label = get_label(list_label, lx)))
			lx->valeur = label->octet - buffer->size + 1 + (op->octet ? 1 : 0);
		write_bigendian(&buffer_param, lx->valeur, nb_octet);
	}
	write_to_buffer(buffer, buffer_param.data, buffer_param.size);
	free(buffer_param.data);
}

void	set_codage(unsigned char *codage, t_list *list_lex, t_op *op)
{
	int		i;
	t_lx	*lx;

	i = 0;
	while (i < op->nb_p)
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
