/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 01:43:51 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/23 09:43:38 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	char	*g_delim;

void			find_double_quote_end(t_list **lst2, int first_double,
		int name_cmt)
{
	t_lx	*lx;
	t_list	*lst;
	char	*tmp[2];

	while (lst2 && *lst2)
	{
		lst = *lst2;
		lx = (t_lx*)lst->content;
		lx->type = 6 + name_cmt;
		tmp[0] = ft_strchr(lx->word, '"');
		tmp[1] = ft_strrchr(lx->word, '"');
		if ((first_double && tmp[0] != tmp[1] && *(tmp[1] + 1)
		&& (lx->error = 1)) || (!first_double && tmp[1]
		&& *(tmp[1] + 1) && (lx->error = 1)) || (!first_double && tmp[0]
		&& tmp[1] && tmp[0] != tmp[1] && (lx->error = 1)))
			return ;
		*lst2 = (*lst2)->next;
		if (first_double && tmp[0] != tmp[1] && !*(tmp[1] + 1))
			return ;
		else if (!first_double && tmp[1] && !*(tmp[1] + 1))
			return ;
		first_double = 0;
	}
}

void			set_name_comment(t_list **lst2, t_lx **last_inst)
{
	t_list	*lst;
	t_lx	*lx;

	lst = *lst2;
	lx = lst->content;
	if (lst->next && !ft_strcmp(lx->word, NAME_CMD_STRING))
	{
		*last_inst = lst->content;
		((t_lx *)lst->content)->type = INSTRUCTION;
		*lst2 = lst->next;
		if (*((t_lx*)((*lst2)->content))->word == '"')
			find_double_quote_end(lst2, 1, 0);
		if (!(lst = *lst2))
			return ;
		lx = lst->content;
	}
	if (lst && lst->next && !ft_strcmp(lx->word, COMMENT_CMD_STRING))
	{
		*last_inst = lst->content;
		((t_lx *)lst->content)->type = INSTRUCTION;
		*lst2 = lst->next;
		if (*((t_lx*)((*lst2)->content))->word == '"')
			find_double_quote_end(lst2, 1, 1);
	}
}

static	void	fix_lex(t_lx *lex, t_list **label)
{
	static size_t	index = 0;
	int				decalage;

	decalage = 0;
	if (!lex)
		return ;
	if (++index && lex->type == LABEL)
		add_label(lex, label);
	if (lex->label)
		return ;
	if (lex->type == DIRECT || lex->type == REGISTRE)
		decalage = 1;
	if (lex->type == DIRECT || lex->type == REGISTRE || lex->type == INDIRECT)
	{
		if (!ft_strisnumber(lex->word + decalage))
			lex->error = 4;
		else if (!ft_isint(lex->word + decalage))
			lex->error = 19;
		lex->valeur = ft_atoi(lex->word + decalage);
		if (!lex->error && lex->type == REGISTRE && lex->valeur > 15)
		{
			lex->error = 3;
			lex->error = (lex->error % 16);
		}
	}
}

static	void	set_lex_ext(t_list *lst, t_lx *lx, t_lx *last_inst0)
{
	static	t_lx	*last_inst = NULL;

	if (!last_inst)
		last_inst = last_inst0;
	if (lx->type != -1)
		return ;
	if (is_label(lx->word))
		lx->type = LABEL;
	else if (lx->word[0] == 'r')
		lx->type = REGISTRE;
	else if (is_direct(lst))
		return ;
	else if (is_indirect(lst))
		return ;
	else if (lx->word[0] == SEPARATOR_CHAR)
		lx->type = SEPARATEUR;
	else if (!last_inst || last_inst->pos[0] != lx->pos[0])
	{
		lx->type = INSTRUCTION;
		last_inst = lx;
	}
	else
		lx->error = 1;
}

void			set_lex(t_list *lst, t_list **label)
{
	t_lx	*lx;
	t_lx	*last_inst;

	last_inst = NULL;
	set_name_comment(&lst, &last_inst);
	while (lst)
	{
		lx = lst->content;
		set_lex_ext(lst, lx, last_inst);
		fix_lex(lx, label);
		lst = lst->next;
	}
}
