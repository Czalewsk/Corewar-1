/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/03/27 18:07:29 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_lx		*lx_next_line(t_list *list_lex, size_t last_line)
{
	t_lx	*lx;

	while (list_lex)
	{
		lx = list_lex->content;
		if (lx->pos[0] > last_line)
			return (lx);
		list_lex = list_lex->next;
	}
	return (NULL);
}

void	parse(t_list *list_lex)
{
	size_t	current_line;
	t_lx	*lx;

	current_line = 0;
	while ((lx = lx_next_line(list_lex, current_line)) != NULL)
	{
		ft_printf("First word: %s\n", lx->word);
		current_line = lx->pos[0];
	}
}