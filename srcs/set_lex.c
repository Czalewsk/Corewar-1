/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 01:43:51 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/24 01:44:27 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	set_lex(t_list *lst)
{
	t_lx	*lx;
	while (lst)
	{
		lx = lst->content;
		if (lst->next && !ft_strcmp(((t_lx *)lst->next->content)->word, ":")
			&& lx->word[0] != '%')
			lx->type = 3;
		else if (lst->next && lst->next->next && lx->word[0] == '%'
			&& !ft_strcmp(((t_lx *)lst->next->content)->word, ":"))
			((t_lx *)lst->next->next->content)->type = 3;
		else if (lx->word[0] == '%')
			lx->type = 1;
		else if (lx->word[0] == 'r')
			lx->type = 4;
		else if (ft_strisnumber(lx->word))
			lx->type = 2;
		else if (lx->type == 0 && !ft_strchr(g_delim, lx->word[0]))
			lx->type = 5;
		lst = lst->next;
	}
}
