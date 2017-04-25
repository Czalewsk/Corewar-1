/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 01:43:51 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/25 11:20:04 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	char	*g_delim;

void			find_double_quote_end(t_list **lst2, int first_double,
		int name_cmt)
{
	t_lx	*lx;
	t_list	*lst;
	int		len;
	int		close;

	close = 0;
	while (lst2 && *lst2 && !close)
	{
		lst = *lst2;
		lx = (t_lx*)lst->content;
		len = ft_strlen(lx->word);
		lx->type = 6 + name_cmt;
		if (!len || lx->word[len - 1] == '"')
			close = 1;
		*lst2 = (*lst2)->next;
		if (!first_double)
			return ;
	}
}

void			set_name_comment(t_list **lst2)
{
	t_list	*lst;
	t_lx	*lx;
	int		close;

	close = 0;
	lst = *lst2;
	lx = lst->content;
	if (lst->next && !ft_strcmp(lx->word, NAME_CMD_STRING))
	{
		((t_lx *)lst->content)->type = INSTRUCTION;
		*lst2 = lst->next; *((t_lx*)((*lst2)->content))->word == '"' ?
		find_double_quote_end(lst2, 1, 0) : find_double_quote_end(lst2, 0, 0);
		lst = *lst2;
		lx = lst->content;
	}
	if (lst && lst->next && !ft_strcmp(lx->word, COMMENT_CMD_STRING))
	{
		((t_lx *)lst->content)->type = INSTRUCTION;
		*lst2 = lst->next; *((t_lx*)((*lst2)->content))->word == '"' ?
		find_double_quote_end(lst2, 1, 1) : find_double_quote_end(lst2, 0, 1);
	}
}

static	void	fix_lex(t_lx *lex, t_list **label)
{
	static size_t	index = 0;

	if (!lex)
		return ;
	if (++index && lex->type == LABEL)
		add_label(lex, label);
	if (lex->label)
		return ;
	else if (lex->type == DIRECT || lex->type == REGISTRE)
	{
		if (!ft_isint(lex->word + 1))
			lex->error = 19;
		lex->valeur = ft_atoi(lex->word + 1);

	}
	else if (lex->type == INDIRECT)
	{
		if (!ft_isint(lex->word))
			lex->error = 19;
		lex->valeur = ft_atoi(lex->word);
	}
}

static	void	set_lex_ext(t_list *lst, t_lx *lx)
{
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
	else
		lx->type = INSTRUCTION;
}

void			set_lex(t_list *lst, t_list **label)
{
	t_lx	*lx;

	set_name_comment(&lst);
	while (lst)
	{
		lx = lst->content;
		set_lex_ext(lst, lx);
		fix_lex(lx, label);
		lst = lst->next;
	}
}
