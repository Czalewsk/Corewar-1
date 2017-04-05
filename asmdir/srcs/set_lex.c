/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 01:43:51 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/05 16:11:22 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	char	*g_delim;

	const t_gramm	(gramm)[8] = {
	{0, '%', NULL, 1000000},
	{0, ':', NULL, 100000},
	{0, 'r', &ft_isint, 10000},
	{0, '%', &ft_isint, 1000},
	{1, '\0', &ft_isint, 100},
	{1, '\0', &is_labelchar, 10},
	{1, ':', &is_labelchar, 1},
	{0, 0, NULL, 0},
	};

static	void	add_label(t_lx *lx, t_list **label, size_t index)
{
	t_label		*new;

	if (!label || !(new = ft_memalloc(sizeof(t_label))))
		return ;
	new->name = lx->word;
	new->index = index;
	ft_lst_pushend(label, ft_lstnew(new, sizeof(t_label)));
	ft_memdel((void**)&new);
}

static	void	fix_lex(t_lx *lex, t_list **label)
{
	static size_t	index = 0;

	if (!lex)
		return ;
	if (lex->type == DIRECT && ft_strisnumber(lex->word + 1))
		lex->valeur = ft_atoi(lex->word + 1);
	else if (lex->type == INDIRECT)
		lex->valeur = ft_atoi(lex->word);
	else if (lex->type == REGISTRE && ft_strisnumber(lex->word + 1))
		lex->valeur = ft_atoi(lex->word + 1);
	if (++index && lex->type == D_LABEL)
		add_label(lex, label, index);
}

static	void	set_lex_ext(t_list *lst, t_lx *lx)
{
	if (lst->next && !ft_strcmp(lx->word, NAME_CMD_STRING))
		((t_lx *)lst->next->content)->type = NAME;
	if (lst->next && !ft_strcmp(lx->word, COMMENT_CMD_STRING))
		((t_lx *)lst->next->content)->type = COMMENT;
}

void			set_lex(t_list *lst, t_list **label)
{
	t_lx	*lx;

	while (lst)
	{
		lx = lst->content;
		set_lex_ext(lst, lx);
		fix_lex(lx, label);
		lst = lst->next;
	}
	printf("i= %i | s=%c| %p\n", gramm[0].value, gramm[0].format, gramm[0].f);
	printf("i= %i | s=%c| %p\n", gramm[1].value, gramm[1].format, gramm[1].f);
	printf("i= %i | s=%c| %p\n", gramm[4].value, gramm[4].format, gramm[4].f);
	printf("i= %i | s=%c| %p\n", gramm[6].value, gramm[6].format, gramm[6].f);
}
