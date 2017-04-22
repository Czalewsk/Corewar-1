/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 19:53:04 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/22 19:54:45 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_label(t_lx *lx, t_list **label)
{
	t_label		*new;
	char		*tmp;

	if (!label || !(new = ft_memalloc(sizeof(t_label))))
		return ;
	new->name = lx->word;
	tmp = ft_strrchr(new->name, LABEL_CHAR);
	*tmp = 0;
	new->octet = -1;
	ft_lst_pushend(label, ft_lstnew(new, sizeof(t_label)));
	ft_memdel((void**)&new);
}
