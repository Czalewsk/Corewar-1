/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:49:28 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/23 07:01:46 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				check_multiple_dquote(t_list **lst2)
{
	t_lx	*lx;
	size_t		line;

	if (!*lst2)
		return (0);
	lx = (*lst2)->content;
	line = lx->pos[0];
	if (!((ft_howmany(lx->word, '\"') > 2)))
		return (1);
	lx->error = 1;
	while (*lst2 && line == lx->pos[0])
	{
		*lst2 = (*lst2)->next;
		lx = (*lst2) ? (*lst2)->content : NULL;
	}
	return (0);
}

void		fill_header_name_cmt(header_t *header, int i, char *tmp,
		int len_total)
{
	if (len_total < 3)
		return ;
	i ? ft_memset(header->comment, 0, COMMENT_LENGTH) :
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH);
	i ? ft_strcpy(header->comment, tmp + 1) :
		ft_strcpy(header->prog_name, tmp + 1);
}
/*
int			find_end_dquote(t_lx *elmt, t_list **lst, int i, header_t *header)
{
	int		len;
	int		len_total;
	char	*tmp;
	int		end;

	end = 0;
	len_total = 0;
	tmp = ft_strdup("");
	while (*lst && !end && (elmt = (*lst)->content))
	{
		len_total += (len = ft_strlen(elmt->word));
		end = len_total > 1 && elmt->word[len - 1] == '\"' ? 1 : 0;
		tmp = (end) ? tmp : ft_strjoin_free(tmp, 1, elmt->word, 0);
		(*lst) = (*lst)->next;
	}
		tmp = ft_strjoin_free(tmp, 1, ft_strsub(elmt->word, 0, len - 1), 1);
		if (len_total - 2 > ((i) ? COMMENT_LENGTH : PROG_NAME_LENGTH) &&
		(elmt->error = i ? 12 : 11))
			tmp[(i) ? COMMENT_LENGTH : PROG_NAME_LENGTH] = '\0';
		fill_header_name_cmt(header, i, tmp, len_total);
	ft_strdel(&tmp);
	return (*lst ? 1 : 0);
}

void		check_name_cmt(t_list **lst, int i, header_t *header)
{
	t_lx	*elmt;
	
	if (!*lst)
		return ;
	elmt = (*lst)->content;
	if (elmt->type != INSTRUCTION || (i ?
	ft_strcmp(elmt->word, COMMENT_CMD_STRING) :
	ft_strcmp(elmt->word, NAME_CMD_STRING)))
		elmt->error += i ? 15 : 14;
	else if ((*lst)->next)
	{
		(*lst) = (*lst)->next;
		elmt = (*lst)->content;
		if (elmt->word[0] == '\"')
			elmt->error = find_end_dquote(elmt, lst, i, header) ?
				elmt->error : 24;
		else
			elmt->error = 9;
	}
}
*/

void		check_comment(t_list **lst, header_t *header)
{
	t_lx	*lx;
	int		nb;
	char	*tmp;

	lx = NULL;
	nb = 0;
	tmp = ft_strdup("");
	if (*lst && (lx = (*lst)->content) && !ft_strcmp(lx->word, COMMENT_CMD_STRING))
		*lst = (*lst)->next;
	else if (lx && (lx->error += 15))
		return ;
	if (!check_multiple_dquote(lst))
		return ;
	while (*lst && (lx = (*lst)->content) && lx->type == COMMENT && ++nb)
	{
		tmp = ft_strjoin_free(tmp, 1, lx->word, 0);
		*lst = (*lst)->next;
	}
	if ((lx && !nb))
		lx->error = 24;
	if (tmp)
		tmp[ft_strlen(tmp) - 1] = 0;
	if (lx && !*lst)
		lx->error = 25;
	fill_header_name_cmt(header, 1, tmp, ft_strlen(tmp));
}

void		check_name(t_list **lst, header_t *header)
{
	t_lx	*lx;
	int		nb;
	char	*tmp;

	lx = NULL;
	nb = 0;
	tmp = ft_strdup("");
	if (*lst && (lx = (*lst)->content) && !ft_strcmp(lx->word, NAME_CMD_STRING))
		*lst = (*lst)->next;
	else if (lx && (lx->error = 14))
		return ;
	if (!check_multiple_dquote(lst))
		return ;
	while (*lst && (lx = (*lst)->content) && lx->type == NAME && ++nb)
	{
		tmp = ft_strjoin_free(tmp, 1, lx->word, 0);
		*lst = (*lst)->next;
	}
	if (tmp)
		tmp[ft_strlen(tmp) - 1] = 0;
	if (lx && !nb)
		lx->error = 24;
	fill_header_name_cmt(header, 0, tmp, ft_strlen(tmp));
}

void		check_name_and_cmt(t_list **lst, header_t *header)
{
	(void)lst;(void)header;
	check_name(lst, header);
//	check_name_cmt(lst, 0, header);
	check_comment(lst, header);
//	check_name_cmt(lst, 1, header);
}

int			check_label_chars(t_list *lst)
{
	char		*str;
	t_label		*label;

	while (lst)
	{
		label = lst->content;
		str = label->name;
		while (*str)
		{
			if (!ft_strchr(LABEL_CHARS, *str))
			{
				label->lx->error = 10;
				return (0);
			}
			++str;
		}
		lst = lst->next;
	}
	return (1);
}
