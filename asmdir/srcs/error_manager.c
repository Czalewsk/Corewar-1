/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:14:32 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/22 20:23:42 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_error(t_list *curs)
{
	int		force_quit;
	t_lx	*lx;

	force_quit = 0;
	while (curs && !force_quit)
	{
		lx = curs->content;
		if (lx->error > 0)
			force_quit = 1;
		curs = curs->next;
	}
	if (force_quit)
		main_error("Error in lexer/parser\nProgramm hasn't finished", 1);
}