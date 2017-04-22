/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:49:28 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/22 19:49:28 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		fill_header_name_cmt(header_t *header, int i, char *tmp,
		int len_total)
{
	if (len_total < 3)
	{
		if (i)
			header->comment[0] = '\0';
		else
			header->prog_name[0] = '\0';
		return ;
	}
	i ? ft_strcpy(header->comment, tmp + 1) :
		ft_strcpy(header->prog_name, tmp + 1);
}

void		find_end_dquote(t_lx *elmt, t_list **lst, int i, header_t *header)
{
	int		len;
	int		len_total;
	char	*tmp;
	int		end;

	end = 0;
	len_total = 0;
	tmp = ft_strdup("");
	while (*lst && !end)
	{
		elmt = (*lst)->content;
		len = ft_strlen(elmt->word);
		len_total += len;
		end = len_total > 1 && elmt->word[len - 1] == '\"' ? 1 : 0;
		tmp = (end) ? tmp : ft_strjoin_free(tmp, 1, elmt->word, 0);
		(*lst) = (*lst)->next;
	}
	if (!(*lst) && (elmt->error = (i) ? 0x8000000 : 0x4000000))
		return ;
	tmp = ft_strjoin_free(tmp, 1, ft_strsub(elmt->word, 0, len - 1), 1);
	if (len_total - 2 > ((i) ? COMMENT_LENGTH : PROG_NAME_LENGTH) &&
			(elmt->error = i ? 0x2000000 : 0x1000000))
		tmp[(i) ? COMMENT_LENGTH : PROG_NAME_LENGTH] = '\0';
	fill_header_name_cmt(header, i, tmp, len_total);
	ft_strdel(&tmp);
}

void		check_name_cmt(t_list **lst, int i, header_t *header)
{
	t_lx	*elmt;

	elmt = (*lst)->content;
	if (elmt->type != INSTRUCTION || (i ?
	ft_strcmp(elmt->word, COMMENT_CMD_STRING) :
	ft_strcmp(elmt->word, NAME_CMD_STRING)))
		elmt->error = i ? 0x80000000 : 0x40000000;
	else
	{
		(*lst) = (*lst)->next;
		elmt = (*lst)->content;
		if (elmt->word[0] == '\"')
			find_end_dquote(elmt, lst, i, header);
		else
			elmt->error = i ? 0x20000000 : 0x10000000;
	}
}

void		check_name_and_cmt(t_list **lst, header_t *header)
{
	check_name_cmt(lst, 0, header);
	check_name_cmt(lst, 1, header);
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
