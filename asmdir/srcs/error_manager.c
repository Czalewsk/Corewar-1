/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:14:32 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/27 13:30:59 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	t_tab_error	g_tab_error[];
extern	t_op		g_op_tab[];
extern	char		*type[];
extern	t_list		*g_files;

void				set_error_msg(t_lx *lx, char *msg[])
{
	if ((g_tab_error[lx->error - 1]).nb_arg)
	{
		if (lx->error == 6)
			msg[0] = ft_strdup(type[lx->type]);
		else
			msg[0] = ft_strdup(lx->word);
	}
	if ((g_tab_error[lx->error - 1]).nb_arg > 1)
	{
		if (lx->error == 7 )
			msg[1] = ft_itoa(lx->param_error);
		else
			msg[1] = ft_itoa((get_instruction(lx))->type_param[0]);
	}
	if ((g_tab_error[lx->error - 1]).nb_arg > 2)
	{
		msg[2] = ft_itoa((get_instruction(lx))->nb_p);
	}
}

void				check_error(t_list *curs)
{
	int		force_quit;
	t_lx	*lx;
	char	*msg[3];

	force_quit = 0;
	while (curs)
	{
		lx = curs->content;
		if (lx->error > 0)
		{
			if (!g_tab_error[lx->error - 1].warning)
				force_quit = 1;
			if (!g_tab_error[lx->error - 1].warning)
				ft_printf("{red}Error  ");
			else
				ft_printf("{yellow}Warning  ");
			if (g_tab_error[lx->error - 1].nb_arg)
				set_error_msg(lx, msg);
			ft_printf("Line [%3i] col[%3i] {eoc}: ", lx->pos[0], lx->pos[1]);
			ft_printf(g_tab_error[lx->error - 1].msg, msg[0], msg[1], msg[2]);
			write(1, "\n", 1);
			ft_printf("%s\n", *(char**)
					(ft_lst_return_index(g_files, lx->pos[0] - 1)->content));
			write(1, "\n", 1);
		}
		curs = curs->next;
	}
	if (force_quit)
		main_error("Error in lexer/parser\nProgramm hasn't finished", 1);
}
