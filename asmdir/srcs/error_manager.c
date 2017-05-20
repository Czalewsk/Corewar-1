/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:14:32 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/20 02:33:23 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	t_tab_error	g_tab_error[];
extern	t_op		g_op_tab[];
extern	char		*g_type[];

const	char	*g_type_arg[4] = {"Register", "Direct", "Indirect"};

char			*get_type_wrong_arg(t_list *curs, int wrong)
{
	t_lx	*lx;

	while (wrong-- && curs)
	{
		curs = (curs->next) ? curs->next : curs;
		lx = (curs->content) ? curs->content : NULL;
		while (curs && lx && (lx->type == SEPARATEUR || lx->type == DIRECTCHAR))
		{
			if (!curs->next)
				break ;
			curs = curs->next;
			lx = (curs->content) ? curs->content : NULL;
		}
	}
	return (ft_strdup(g_type[lx->type]));
}

char			*set_arg_msg(t_op *op, int arg_index)
{
	unsigned int	arg;
	unsigned int	bit_one;
	char			*msg;
	int				i;

	msg = ft_strdup("");
	arg = op->type_param[arg_index - 1];
	arg = arg - ((arg >> 1) & 0x55555555);
	arg = (arg & 0x33333333) + ((arg >> 2) & 0x33333333);
	bit_one = (((arg + (arg >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24;
	arg = op->type_param[arg_index - 1];
	while (bit_one-- > 0 && (i = -1))
	{
		while (++i < 3)
		{
			if (arg & (1 << i))
			{
				arg ^= (1 << i);
				msg = ft_strjoin_free(msg, 1, (char*)g_type_arg[i], 0);
				break ;
			}
		}
		msg = (bit_one > 0) ? ft_strjoin_free(msg, 1, " or ", 0) : msg;
	}
	return (msg);
}

int				set_error_msg(t_lx *lx, char *msg[], t_list *curs)
{
	int		nb_arg;

	nb_arg = g_tab_error[lx->error - 1].nb_arg;
	if (nb_arg)
	{
		if (lx->error == 6)
			msg[0] = get_type_wrong_arg(curs, lx->param_error);
		else
			msg[0] = ft_strdup(lx->word);
	}
	if (nb_arg > 1)
	{
		if (lx->error == 7)
			msg[1] = ft_itoa(lx->param_error);
		else
			msg[1] = set_arg_msg((get_instruction(lx)), lx->param_error);
	}
	if (nb_arg > 2)
		msg[2] = ft_itoa((get_instruction(lx))->nb_p);
	return (nb_arg);
}

int				check_error(t_list *curs)
{
	int		force_quit;
	t_lx	*lx;
	char	*msg[3];
	int		nb_free;

	force_quit = 0;
	while (curs && (lx = curs->content))
	{
		lx->error = (lx->error > 29) ? 29 : lx->error; // A delete
		if (lx->error > 0)
		{
			force_quit = (!g_tab_error[lx->error - 1].warning) ? 1 : 0;
			g_tab_error[lx->error - 1].warning ? ft_printf("{yellow}Warning  ")
				: ft_printf("{red}Error  ");
			nb_free = set_error_msg(lx, msg, curs);
			ft_printf("Line [%3i] col[%3i] {eoc}: ", lx->pos[0], lx->pos[1]);
			ft_printf(g_tab_error[lx->error - 1].msg, msg[0], msg[1], msg[2]);
			underline_error(lx, curs, get_gdata());
			while (nb_free)
				ft_strdel(&(msg[--nb_free]));
		}
		curs = curs->next;
	}
	return (force_quit);
}
