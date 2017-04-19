/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:49:28 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/16 16:11:44 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_name(t_list **lst)
{
	t_lx		*elmt;
	size_t		line;
	int			len;

	elmt = (*lst)->content;
	line = elmt->pos[0];
	if (elmt->type == INSTRUCTION && !ft_strcmp(elmt->word, NAME_CMD_STRING))
	{
		(*lst) = (*lst)->next;
		elmt = (*lst)->content;
		len = ft_strlen(elmt->word);
		if (!(elmt->word[0] == '\"' && elmt->word[len - 1] == '\"'))
			elmt->error = 0x8800;
		else if (len > PROG_NAME_LENGTH)
		{
			elmt->word[PROG_NAME_LENGTH] = '\0';
			elmt->error = 0x8000;
		}
		(*lst) = (*lst)->next;
	}
	else if ((elmt->error = 0x4000))
		while (line == ((t_lx*)((*lst)->content))->pos[0])
			(*lst) = (*lst)->next;
}

void		check_comment(t_list **lst)
{
	t_lx		*elmt;
	size_t		line;
	int			len;

	elmt = (*lst)->content;
	line = elmt->pos[0];
	if (elmt->type == INSTRUCTION && !ft_strcmp(elmt->word, COMMENT_CMD_STRING))
	{
		(*lst) = (*lst)->next;
		elmt = (*lst)->content;
		len = ft_strlen(elmt->word);
		if (!(elmt->word[0] == '\"' && elmt->word[len - 1] == '\"'))
			elmt->error = 0x2800;
		else if (len > COMMENT_LENGTH)
		{
			elmt->word[PROG_NAME_LENGTH] = '\0';
			elmt->error = 0x2000;
		}
		(*lst) = (*lst)->next;
	}
	else if ((elmt->error = 0x1000))
		while (line == ((t_lx*)((*lst)->content))->pos[0])
			(*lst) = (*lst)->next;
}

void		check_name_and_cmt(t_list **lst)
{
	check_name(lst);
	check_comment(lst);
}

int			check_label_chars(t_list *lst)
{
	char	*str;

	while (lst)
	{
		str = ((t_label*)lst->content)->name;
		while (*str)
		{
			if (!ft_strchr(LABEL_CHARS, *str))
				return (0);
			++str;
		}
		lst = lst->next;
	}
	return (1);
}
