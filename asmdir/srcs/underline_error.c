/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underline_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 09:34:28 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/02 11:43:29 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	t_list		*g_files;

t_lx			*get_wrong_arg(t_lx *lx, t_list **curs, int wrong)
{
	while (wrong-- && (*curs))
	{
		(*curs) = (*curs)->next;
		lx = ((*curs)->content) ? (*curs)->content : NULL;
		while (*curs && lx && (lx->type == SEPARATEUR || lx->type == DIRECTCHAR))
		{
			(*curs) = (*curs)->next;
			lx = ((*curs)->content) ? (*curs)->content : NULL;
		}
	}
	return (lx);
}

size_t				find_end_error(t_lx *lx, t_list *curs, char *line, size_t begin)
{
	size_t		end;
	size_t		i;
	size_t		index_end;

	i = 0;
	end = 0;
	if (curs->next && ((t_lx*)(curs->next->content))->pos[0] == lx->pos[0])
		index_end = ((t_lx*)(curs->next->content))->pos[1];
	else
		index_end = ft_strlen(line);
	while ((line + i) && i <= index_end)
		end += (line[i++] == '\t') ? 8 - (end % 8) : 1;
	return ((begin > end) ? 0 : end - begin - 1);
}

int				find_begin_error(t_lx *lx, t_list **curs, char *line)
{
	size_t	i;
	int		spaces;

	spaces = 0;
	i = 0;
	if (lx->error == 6)
		lx = get_wrong_arg(lx, curs, lx->param_error);
	else if (lx->error == 7)
		lx = get_wrong_arg(lx, curs, 1);
	while ((line + i) && i <= lx->pos[1])
		spaces += (line[i++] == '\t') ? 8 - (spaces % 8) : 1;
	return (spaces);
}

void			underline_error(t_lx *lx, t_list *curs)
{
	char			*line;
	size_t				begin;
	const	char	tild[21] = "~~~~~~~~~~~~~~~~~~~~~";
	int				end;

	write(1, "\n", 1);
	if (lx->error == 11 || lx->error == 12)
		return ;
	line = *(char**)ft_lst_return_index(g_files, lx->pos[0] - 1)->content;
	ft_printf("%s\n", line);
	begin = find_begin_error(lx, &curs, line);
	end = find_end_error(lx, curs, line, begin);
//	ft_printf("begin = %i | end = %i\n", begin, end);
	ft_printf("{green}%*c", begin,'~');
	while (end > 0)
	{
		write(1, &tild, (end % 20));
		end -= ((end % 20) + 1);
	}
	ft_printf("{eoc}\n\n");
}

