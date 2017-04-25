/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:14:32 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/25 19:33:57 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	t_tab_error	g_tab_error[];

void				check_error(t_list *curs)
{
	int		force_quit;
	t_lx	*lx;

	force_quit = 0;
	while (curs && !force_quit)
	{
		lx = curs->content;
		if (lx->error > 0)
		{
			if (!g_tab_error[lx->error - 1].warning)
				force_quit = 1;
			if (!g_tab_error[lx->error - 1].warning)
				ft_printf("{yellow}Error  {eoc}");
			else
				ft_printf("{yellow}Warning  {eoc}");
			ft_printf("Line [%3i] col[%3i] : ", lx->pos[0], lx->pos[1]);
			ft_printf(g_tab_error[lx->error - 1].msg, lx->word);
			ft_putchar('\n');
		}
		curs = curs->next;
	}
	if (force_quit)
		main_error("Error in lexer/parser\nProgramm hasn't finished", 1);
}
