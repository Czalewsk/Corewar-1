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
		*codage = (*codage | (1 << (6 - i*2)));
	else if (lx->type == DIRECT)
		*codage = (*codage | (2 << (6 - i*2)));
	else if (lx->type == INDIRECT)
		*codage = (*codage | (3 << (6 - i*2)));
}

void	param_to_buffer(t_buf *buffer, t_lx *lx, t_op *op)
{
	(void)buffer;
	int	nb_octet;

	nb_octet = 0;
	if (op->index && lx->type == DIRECT)
		nb_octet = 2;
	else if (lx->type == INDIRECT)
		nb_octet = 2;
	else if (lx->type == REGISTRE)
		nb_octet = 1;
	else if (lx->type == DIRECT)
		nb_octet = 4;
	ft_printf("Writing param %s: %d => %d octet\n", lx->word, lx->valeur, nb_octet);
	// Write the param to (buffer)param now
}

void	write_field(t_buf *buffer, t_list **list_lex)
{
	t_op		*op;
	int		i;
	unsigned char	codage;

	codage = 0;	
	if ((op = get_instruction((*list_lex)->content)))
	{
		i = 0;
		ft_printf("Writing instruction %s: %#04x\n", op->name, op->op_code);
		while (i < op->nb_param)
		{
			*list_lex = get_next_field(*list_lex);
			set_codage(&codage, (*list_lex)->content, i);
			param_to_buffer(buffer, (*list_lex)->content, op);
			++i;
		}
		ft_printf("CODAGE %#04x\n", codage);
		// Write instruction to buffer
		// Write codage to buffer
		// Write (buffer)param to buffer
	}
}

void	write_player(t_buf *buffer, t_list *list_lex)
{
	ft_printf("Writing player started\n");
	(void)buffer;

	while (list_lex)
	{
		write_field(buffer, &list_lex);
		list_lex = get_next_field(list_lex);
	}
	ft_printf("Writing player finished\n");
}
