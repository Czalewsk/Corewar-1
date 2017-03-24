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

#include "lexer.h"

int		main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	t_list		*lex;
	ft_printf("PROGRAM STARTED\n");
	lex = get_lex(av[1]);
	ft_printf("get_lex OK\n");
	if (!lex)
		ft_printf("ERROR LEX IS NULL\n");
	ft_lstiter(lex, &debug_lxcontent);
	ft_printf("PROGRAM FINISHED\n");
	return (0);
}
