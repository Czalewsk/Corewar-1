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
	int		i;
	size_t	line;
	
	lx = (*list_lex)->content;
	line = lx->pos[0];
	ft_printf("Parse instruction: %s\n", lx->word); // DEBUG A DELETE
	(*list_lex) = (*list_lex)->next;
	i = 0;
	while (lx->pos[0] != line)
	{
		lx = (*list_lex)->content;
		if (lx->pos[0] != line)
		{
			ft_printf("Error: Too few argument at line %d\n", line);
			return (0);
		}
		if (arg_isvalid(op, i, list_lex))
			ft_printf("Arg %d is ok\n", i);
		else
			ft_printf("Arg %d is wrong\n", i);
		++i;
	}
	if (!(*list_lex))
		return (0);
	lx = (*list_lex)->content;
	if (lx->pos[0] == line)
		ft_printf("Error: Too many argument at line %d\n", line);
	return (0);
} 

int		parse_label(t_list *list_lex)
{
	t_lx	*lx;
	lx = list_lex->content;

	ft_printf("Parse label: %s\n", lx->word); // DEBUG A DELETE
	if (check_label_chars(lx->word, LABEL_CHARS))
		return (0);
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
		error = parse_label(*list_lex);
		if (is_ref(get_next_lx(*list_lex), LABEL)
			&& get_line(lx) == get_line(get_next_lx(*list_lex)))
			ft_putendl("Error 2 label on the same line");
		if (error)
			ft_putendl("Error label character");
		*list_lex = get_next_lst((*list_lex));
	}
	if ((op = get_instruction((*list_lex)->content)))
		error += parse_instruction(list_lex, op);
	else
		*list_lex = get_next_lst((*list_lex));
}

void	parse(t_list *list_lex)
{
	//check_name_and_cmt(list_lex);
	while (list_lex)
	{
		parse_line(&list_lex);
	}
}
