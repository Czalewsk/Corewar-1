/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 01:43:51 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/24 06:08:12 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static	void	fix_lex(t_lx *lex)
{
	if (!lex)
		return ;
	if (lex->type == DIRECT && ft_strisnumber(lex->word + 1))
		lex->valeur = ft_atoi(lex->word + 1);
	else if (lex->type == INDIRECT)
		lex->valeur = ft_atoi(lex->word);
	else if (lex->type == REGISTRE && ft_strisnumber(lex->word + 1))
		lex->valeur = ft_atoi(lex->word + 1);
}

void	set_lex(t_list *lst)
{
	t_lx	*lx;
	while (lst)
	{
		lx = lst->content;
		if (ft_strchr(g_delim, lx->word[0]))
			lx->type = SEPARATEUR;
		else if (lst->next && !ft_strcmp(((t_lx *)lst->next->content)->word,
					":") && lx->word[0] != '%')
			lx->type = LABEL;
		else if (lst->next && lst->next->next && lx->word[0] == '%'
			&& !ft_strcmp(((t_lx *)lst->next->content)->word, ":"))
			((t_lx *)lst->next->next->content)->type = 3;
		else if (lx->word[0] == '%')
			lx->type = DIRECT;
		else if (lx->word[0] == 'r')
			lx->type = REGISTRE;
		else if (ft_strisnumber(lx->word))
			lx->type = INDIRECT;
		else if (lx->type == 0 && !ft_strchr(g_delim, lx->word[0]))
			lx->type = INSTRUCTION;
		fix_lex(lx);
		lst = lst->next;
	}
}
