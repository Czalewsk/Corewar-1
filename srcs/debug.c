/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:41:57 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/24 06:12:14 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	debug_lxcontent(t_list *lst)
{
	t_lx	*lex;

	lex = lst->content;
	ft_printf("[%2jd][%2jd] %15s", lex->pos[0], lex->pos[1], lex->word);
	ft_printf(" | type = %i", lex->type);
	if (lex->valeur != -1)
		ft_printf(" | valeur = %i", lex->valeur);
	ft_putendl("");
}
