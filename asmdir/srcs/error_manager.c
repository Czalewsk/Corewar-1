/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 20:14:32 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/27 17:34:51 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	t_tab_error	g_tab_error[];
extern	t_op		g_op_tab[];
extern	char		*type[];
extern	t_list		*g_files;

const	char	*type_arg[4] = {"Register", "Direct", "Indirect"};

char				*get_type_wrong_arg(t_list *curs, int wrong)
{
	t_lx	*lx;

	while (wrong-- && curs)
	{
		curs = curs->next;
		lx = (curs->content) ? curs->content : NULL;
		while (curs && lx && (lx->type == SEPARATEUR || lx->type == DIRECTCHAR))
		{
			curs = curs->next;
			lx = (curs->content) ? curs->content : NULL;
		}
	}
	return (ft_strdup(type[lx->type]));
}

char				*set_arg_msg(t_op *op, int arg_index)
{
	unsigned int	arg;
	unsigned int	bit_one; // store the total here
	char			*msg;
	int				i;
	int				type_param;

	msg = ft_strdup("");
	arg = op->type_param[arg_index - 1];
	type_param = arg;
	arg = arg - ((arg >> 1) & 0x55555555);    // reuse input as temporary
	arg = (arg & 0x33333333) + ((arg >> 2) & 0x33333333);   // temp
	bit_one = (((arg + (arg >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24; // count
	while (bit_one-- > 0 && !(i = 0))
	{
		while (i < 3)
		{
			if (type_param & (1 << i))
			{
				type_param ^= i;
				msg = ft_strjoin_free(msg, 1, (char*)type_arg[i], 0);
				break ;
			}
			i++;
		}
		msg = (bit_one > 1) ? ft_strjoin_free(msg, 1, " or ", 0) : msg;
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
		if (lx->error == 7 )
			msg[1] = ft_itoa(lx->param_error);
		else
			msg[1] = set_arg_msg((get_instruction(lx)), lx->param_error);
	}
	if (nb_arg > 2)
		msg[2] = ft_itoa((get_instruction(lx))->nb_p);
	return (nb_arg);
}

void				check_error(t_list *curs)
{
	int		force_quit;
	t_lx	*lx;
	char	*msg[3];
	int		nb_free;

	nb_free = 0;
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
				nb_free = set_error_msg(lx, msg, curs);
			ft_printf("Line [%3i] col[%3i] {eoc}: ", lx->pos[0], lx->pos[1]);
			ft_printf(g_tab_error[lx->error - 1].msg, msg[0], msg[1], msg[2]);
			write(1, "\n", 1);
			ft_printf("%s\n", *(char**)
					(ft_lst_return_index(g_files, lx->pos[0] - 1)->content));
			write(1, "\n", 1);
			while (nb_free)
				ft_strdel(&(msg[--nb_free]));
		}
		curs = curs->next;
	}
	if (force_quit)
		main_error("Error in lexer/parser\nProgramm hasn't finished", 1);
}
