/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:23:30 by xesnault          #+#    #+#             */
/*   Updated: 2017/03/24 05:35:04 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASM_H

# define __ASM_H

# include "libft.h"
# include "op.h"
# include "lexer.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_buf
{
	void		*data;
	size_t		size;
}			t_buf;

void		parse(t_list *list_lex);

int			write_bin(char *filename, t_buf *buffer);

int			write_to_buffer(t_buf *buffer, void *data, size_t size);

void		header_to_buffer(t_buf *buffer, header_t *header);

t_op		*get_instruction(char *instruction);

int			is_ref(t_lx *lx, int ref);

int			get_line(t_lx *lx);

t_lx		*get_next_lx(t_list *list_lex);

#endif
