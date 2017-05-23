/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 16:58:43 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/23 08:45:09 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_g_files(void *content, size_t size)
{
	(void)size;
	ft_strdel((char**)content);
	free(content);
}

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

void	sp_free(void)
{
	t_gdata	*gdata;

	if (!(gdata = get_gdata()))
		return ;
	if (gdata->lex)
		ft_lstdel(&(gdata->lex), &del_lex);
	if (gdata->label)
		ft_lstdel(&(gdata->label), &del_label);
	if (gdata->g_files)
		ft_lstdel(&(gdata->g_files), &del_g_files);
	if (gdata->buffer_header.data)
		free(gdata->buffer_header.data);
	if (gdata->buffer_prog.data)
		free(gdata->buffer_prog.data);
}
