/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/03/27 18:07:29 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		parse_instruction(t_list **list_lex, t_op *op)
{
	t_lx	*lx;
	lx = (*list_lex)->content;
	
	ft_printf("Parse instruction: %s\n", lx->word);
	(void)list_lex;
	(void)op;
	return (1);
} 

int		parse_label(t_list *list_lex)
{
	t_lx	*lx;
	lx = list_lex->content;

	ft_printf("Parse label: %s\n", lx->word);
	(void)list_lex;
	return (1);
}

void	parse_line(t_list **list_lex)
{
	t_op	*op;
	t_lx	*lx;
	int		error;

	lx = (*list_lex)->content;
	if(is_ref(lx, LABEL))
	{
		parse_label(*list_lex);
		if (is_ref(get_next_lx(*list_lex), LABEL)
			&& get_line(lx) == get_line(get_next_lx(*list_lex)))
			ft_putendl("ok");
		*list_lex = (*list_lex)->next;
	}
	else if ((op = get_instruction(((t_lx *)(*list_lex)->content)->word)))
		error = parse_instruction(list_lex, op);
		// Erreur
/*	while (*list_lex && n++ < i)
	{
		*list_lex = (*list_lex)->next;
	} */
}

void	parse(t_list *list_lex)
{
	//check_name_and_cmt(list_lex);
	while (list_lex)
	{
		parse_line(&list_lex);
		while (1)
			;
	}
}
