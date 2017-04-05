/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 16:44:31 by xesnault          #+#    #+#             */
/*   Updated: 2017/04/04 19:50:57 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

t_op	*get_instruction(t_lx *lx)
{
	int		i;

	i = 0;
	if (lx->type != INSTRUCTION)
		return (0);
	while ((g_op_tab[i]).name)
	{
		if (!ft_strcmp(lx->word, g_op_tab[i].name))
			return (g_op_tab + i);
		++i;
	}
	return (NULL);
}

int		is_ref(t_lx *lx, int ref)
{
	if (!lx || lx->type != ref)
		return (0);
	return (1);
}

int		get_line(t_lx *lx)
{
	if (!lx)
		return (0);
	return (lx->pos[0]);
}

t_lx	*get_next_lx(t_list *list_lex)
{
	if (!list_lex)
		return (NULL);
	list_lex = list_lex->next;
	while (list_lex)
	{
		if (!is_ref(list_lex->content, SEPARATEUR))
			return (list_lex->content);
		list_lex = list_lex->next;
	}
	return (NULL);
}

t_list	*get_next_lst(t_list *list_lex)
{
	if (!list_lex)
		return (NULL);
	list_lex = list_lex->next;
	while (list_lex)
	{
		if (!is_ref(list_lex->content, SEPARATEUR))
			return (list_lex);
		list_lex = list_lex->next;
	}
	return (NULL);
}

t_list	*get_next_field(t_list *list_lex)
{
	if (!list_lex)
		return (NULL);
	list_lex = list_lex->next;
	while (list_lex)
	{
		if (!is_ref(list_lex->content, SEPARATEUR)
				&& !is_ref(list_lex->content, DIRECTCHAR))
			return (list_lex);
		list_lex = list_lex->next;
	}
	return (NULL);
}

int		check_label_chars(t_list *lst)
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

char	get_arg_type(int type)
{
	if (type == REGISTRE)
		return (1);
	if (type == DIRECT)
		return (2);
	if (type == INDIRECT)
		return (4);
	if (type == LABEL)
		return (2);
	return (0);
}

int		arg_isvalid(t_op *op, int i, t_list **list_lex)
{
	t_lx	*lx;

	if (!(*list_lex))
		return (0);
	lx = (*list_lex)->content;
	if (lx->type == DIRECTCHAR)
	{
		*list_lex = (*list_lex)->next;
		lx = (*list_lex)->content;
		if (lx->type == SEPARATEUR && lx->word[0] == LABEL_CHAR)
		{
			*list_lex = (*list_lex)->next;
			lx = (*list_lex)->content;
		}
		else
			return (0);
	}
	*list_lex = (*list_lex)->next;
	if (i < op->nb_param && op->type_param[i] & get_arg_type(lx->type))
		return (1);
	return (0);
}
























