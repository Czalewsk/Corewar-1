/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:45:22 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/24 01:42:56 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	t_list		*lex;
	t_buf		buffer;
	header_t	header;

	buffer.size = 0;
	if (ac != 2)
		return (0);
	g_wspace = " \t";
	g_eol = "#;\n";
	g_delim = ":,";

	ft_printf("PROGRAM STARTED\n");
	lex = get_lex(av[1]);
	ft_printf("get_lex OK\n");
	set_lex(lex);
	ft_printf("Set_lex OK\n");
	if (!lex)
		ft_printf("ERROR LEX IS NULL\n");
	ft_lstiter(lex, &debug_lxcontent);
	ft_memset(header.prog_name, 0, PROG_NAME_LENGTH);
	ft_memset(header.comment, 0, COMMENT_LENGTH);
	ft_strcpy(header.prog_name, "This is a test !");
	ft_strcpy(header.comment, "COMMENT TEST !");
	header.magic = COREWAR_EXEC_MAGIC;
	header.prog_size = 2147483647;
	header_to_buffer(&buffer, &header);
	write_bin("player.cor", &buffer);
	ft_printf("PROGRAM FINISHED\n");
	return (0);
}
