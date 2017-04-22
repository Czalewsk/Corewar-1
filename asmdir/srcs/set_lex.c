/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 01:43:51 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/22 18:30:56 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	char	*g_delim;

static	void	add_label(t_lx *lx, t_list **label)
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
		printf("word=%s\n", lx->word);
		len = ft_strlen(lx->word);
		lx->type = 6 + name_cmt;
		printf("type =%i\n", lx->type);
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
	if (lex->type == DIRECT && ft_strisnumber(lex->word + 1))
		lex->valeur = ft_atoi(lex->word + 1);
	else if (lex->type == INDIRECT && ft_strisnumber(lex->word))
		lex->valeur = ft_atoi(lex->word);
	else if (lex->type == REGISTRE && ft_strisnumber(lex->word + 1))
		if ((lex->valeur = ft_atoi(lex->word + 1)) > 99)
			lex->error = 3;
	if (++index && lex->type == LABEL)
		add_label(lex, label);
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
