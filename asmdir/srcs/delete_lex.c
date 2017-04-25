/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 16:58:43 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/17 09:51:39 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	del_lex(void *content, size_t size)
{
	t_lx	*elmt;

	(void)size;
	elmt = content;
	ft_strdel(&elmt->word);
	free(content);
}

void	del_label(void *content, size_t size)
{
	t_label		*elmt;

	(void)size;
	(void)elmt;
	elmt = content;
	free(content);
}
