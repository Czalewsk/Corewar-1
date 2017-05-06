/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:41:57 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/01 10:53:53 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

const	char	*g_type[] = {"Direct", "Indirect", "Declaration Label",
	"Registre", "Instruction", "Separateur", "Name", "Comment",
	"Direct_Char", "Label", "Label Indirect"};

void	debug_lxcontent(t_list *lst)
{
	t_lx			*lex;

	lex = lst->content;
	ft_printf("[%3jd][%2jd] {green}%-15s{eoc}",
			lex->pos[0], lex->pos[1], lex->word);
	lex->type >= 0 ? ft_printf(" | type = %s", g_type[lex->type]) : 1;
	if (lex->label)
		ft_printf(" | valeur = [%s]", lex->label);
	else if (lex->valeur != -1)
		ft_printf(" | valeur = %i", lex->valeur);
	if (lex->error)
		ft_printf("| Erreur= {red}%i{eoc}", lex->error);
	ft_putendl("");
}

void	debug_labelcontent(t_list *lst)
{
	t_label		*elmt;

	elmt = lst->content;
	ft_printf("[%3i] Name of label : %s\n", elmt->octet, elmt->name);
}

void	debug_print_line(t_list *lst)
{
	ft_printf("%s\n", *(char**)lst->content);
}