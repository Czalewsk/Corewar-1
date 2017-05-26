/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 19:53:04 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/23 09:45:07 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_if_already_exist(t_lx *lx, t_list *list_label)
{
	t_label	*label;

	while (list_label)
	{
		label = list_label->content;
		if (ft_strcmp(label->name, lx->word) == 0)
			lx->error = 8;
		list_label = list_label->next;
	}
}

void	add_label(t_lx *lx, t_list **label)
{
	t_label		*new;
	char		*tmp;

	tmp = ft_strrchr(lx->word, LABEL_CHAR);
	*tmp = 0;
	check_if_already_exist(lx, *label);
	if (!label || !(new = ft_memalloc(sizeof(t_label))))
		return ;
	new->name = lx->word;
	new->lx = lx;
	new->octet = -1;
	ft_lst_pushend(label, ft_lstnew(new, sizeof(t_label)));
	ft_memdel((void**)&new);
}
