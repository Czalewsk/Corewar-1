/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 15:55:33 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/24 08:13:08 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		arg_isvalid(t_list **lst, t_lx *lx, t_op *op, t_list *label)
{
	int		i;

	i = 0;
	if (!(*lst))
		return (0);
	while ((*lst = (*lst)->next) && i < op->nb_p)
	{
		if (*((t_lx*)(*lst)->content)->word == SEPARATOR_CHAR && (*lst)->next)
			*lst = (*lst)->next;
		lx = (*lst)->content;
		if ((lx->type == DIRECTCHAR || *lx->word == LABEL_CHAR) && (*lst)->next)
		{
			*lst = (*lst)->next;
			lx = (*lst)->content;
			if (!parse_label(lx, label))
				return (1);
		}
		if (!(op->type_param[i] & get_arg_type(lx->type)))
			return (0);
		i++;
	}
	return (1);
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
