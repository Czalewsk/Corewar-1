/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:41:57 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/25 12:14:55 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	debug_lxcontent(t_list *lst)
{
	t_lx			*lex;
	const	char	*type[] = {"Direct", "Indirect", "Label", "Registre",
		"Instruction", "Separateur", "Name", "Comment", "Direct_Char"};

	lex = lst->content;
	ft_printf("[%2jd][%2jd] {green}%-15s{eoc}", lex->pos[0], lex->pos[1], lex->word);
	lex->type >= 0 ? ft_printf(" | type = %s", type[lex->type]) : 1;
	if (lex->valeur != -1)
		ft_printf(" | valeur = %i", lex->valeur);
	ft_putendl("");
}
