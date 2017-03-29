/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name_and_cmt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:49:28 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/29 06:29:46 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_name(t_list **lst)
{
	t_lx		*elmt;
	size_t		line;

	elmt = (*lst)->content;
	line = elmt->pos[0];
	if (elmt->type == INSTRUCTION && !ft_strcmp(elmt->word, NAME_CMD_STRING))
	{
		(*lst) = (*lst)->next;
		elmt = (*lst)->content;
		if (ft_strlen(elmt->word) > PROG_NAME_LENGTH)
		{
			elmt->word[PROG_NAME_LENGTH] = '\0';
			elmt->error = 0x8000;
		}
		(*lst) = (*lst)->next;
	}
	else
	{
		elmt->error = 0x4000;
		while (line == ((t_lx*)((*lst)->content))->pos[0])
			(*lst) = (*lst)->next;
	}
}

void		check_comment(t_list **lst)
{
	t_lx		*elmt;
	size_t		line;

	elmt = (*lst)->content;
	line = elmt->pos[0];
	if (elmt->type == INSTRUCTION && !ft_strcmp(elmt->word, COMMENT_CMD_STRING))
	{
		(*lst) = (*lst)->next;
		elmt = (*lst)->content;
		if (ft_strlen(elmt->word) > COMMENT_LENGTH)
		{
			elmt->word[PROG_NAME_LENGTH] = '\0';
			elmt->error = 0x2000;
		}
		(*lst) = (*lst)->next;
	}
	else
	{
		elmt->error = 0x1000;
		while (line == ((t_lx*)((*lst)->content))->pos[0])
			(*lst) = (*lst)->next;
	}
}

void		check_name_and_cmt(t_list **lst)
{
	check_name(lst);
	check_comment(lst);
}