/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 05:49:28 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/23 11:22:42 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				check_multiple_dquote(t_list **lst2)
{
	t_lx		*lx;
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

void			fill_header_name_cmt(header_t *header, int i, char *tmp,
		int len_total)
{
	if (len_total < 3)
		return ;
	i ? ft_memset(header->comment, 0, COMMENT_LENGTH) :
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH);
	i ? ft_strcpy(header->comment, tmp + 1) :
		ft_strcpy(header->prog_name, tmp + 1);
}

void			check_comment(t_list **lst, header_t *header)
{
	t_lx	*lx;
	int		nb;
	char	*tmp;

	lx = NULL;
	nb = 0;
	if (*lst && (lx = (*lst)->content)
			&& !ft_strcmp(lx->word, COMMENT_CMD_STRING))
		*lst = (*lst)->next;
	else if ((lx && (lx->error += 15)) || !check_multiple_dquote(lst))
		return ;
	tmp = ft_strdup("");
	while (*lst && (lx = (*lst)->content) && lx->type == COMMENT && ++nb)
	{
		tmp = ft_strjoin_free(tmp, 1, lx->word, 0);
		*lst = (*lst)->next;
	}
	if ((lx && !nb))
		lx->error = 24;
	if (tmp && ft_strlen(tmp) > 1)
		tmp[ft_strlen(tmp) - 1] = 0;
	if (lx && !*lst)
		lx->error = 25;
	fill_header_name_cmt(header, 1, tmp, ft_strlen(tmp));
	free(tmp);
}

void			check_name(t_list **lst, header_t *header)
{
	t_lx	*lx;
	int		nb;
	char	*tmp;

	lx = NULL;
	nb = 0;
	if (*lst && (lx = (*lst)->content) && !ft_strcmp(lx->word, NAME_CMD_STRING))
		*lst = (*lst)->next;
	else if (lx && (lx->error = 14))
		return ;
	if (!check_multiple_dquote(lst))
		return ;
	tmp = ft_strdup("");
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
	free(tmp);
}

int				check_label_chars(t_list *lst)
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
