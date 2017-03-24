/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:41:57 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/24 01:52:19 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	debug_lxcontent(t_list *lst)
{
	t_lx	*lex;

	lex = lst->content;
	ft_printf("[%2jd][%2jd] %10s | type = %d\n", lex->pos[0], lex->pos[1], lex->word, lex->type);
}
