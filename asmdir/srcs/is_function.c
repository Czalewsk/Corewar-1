/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 15:55:33 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/23 14:29:38 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		arg_isvalid(t_op *op, int i, t_list **list_lex, t_list *label)
{
	t_lx	*lx;

	if (!(*list_lex))
		return (0);
	lx = (*list_lex)->content;
	if (lx->type == SEPARATEUR || lx->type == DIRECTCHAR)
	{
		if ((lx->type == SEPARATEUR || lx->type == DIRECTCHAR) &&
				(lx->word[0] == LABEL_CHAR
				|| (lx->word[0] == DIRECT_CHAR && lx->word[1] == LABEL_CHAR)))
		{
			*list_lex = (*list_lex)->next;
			lx = (*list_lex)->content;
			parse_label(lx, label);
		}
		else
			return (0);
	}
	*list_lex = (*list_lex)->next;
	if (i < op->nb_p && op->type_param[i] & get_arg_type(lx->type))
		return (1);
	return (0);
}

int		is_label(char *word)
{
	char	*c;

	c = ft_strrchr(word, LABEL_CHAR);
	if (!c)
		return (0);
	if (*(c + 1) != 0)
		return (0);
	if (word[0] == DIRECT_CHAR && word[1] == LABEL_CHAR)
		return (0);
	if (word[0] == LABEL_CHAR && !word[1])
		return (0);
	return (1);
}

int		is_direct(t_list *lst)
{
	t_lx	*lx;

	lx = lst->content;
	if (!ft_strcmp(lx->word, "%:"))
	{
		lx->type = DIRECTCHAR;
		lx = lst->next->content;
		lx->type = DIRECT;
		lx->label = lx->word;
		return (1);
	}
	else if (!ft_strncmp(lx->word, "%", 1))
	{
		lx->type = DIRECT;
		return (1);
	}
	return (0);
}

int		is_indirect(t_list *lst)
{
	t_lx	*lx;

	lx = lst->content;
	if (!ft_strcmp(lx->word, ":"))
	{
		lx->type = SEPARATEUR;
		if (!lst->next)
			return (0);
		lx = lst->next->content;
		lx->type = INDIRECT;
		lx->label = lx->word;
		return (1);
	}
	else if (ft_strisnumber(lx->word))
	{
		lx->type = INDIRECT;
		return (1);
	}
	return (0);
}

int		is_ref(t_lx *lx, int ref)
{
	if (!lx || lx->type != ref)
		return (0);
	return (1);
}
