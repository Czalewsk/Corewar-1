/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:45:22 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/22 20:22:36 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	main_error(char *str, int forcequit)
{
	ft_printf("{red}%s{eoc}\n", str);
	if (forcequit)
		exit(1);
}

void	sp_free(t_list *lex, t_list *label, t_buf *buffer1, t_buf *buffer2)
{
	ft_lstdel(&lex, &del_lex);
	ft_lstdel(&label, &del_label);
	free(buffer1->data);
	free(buffer2->data);
}

void	buffer_set_zero(t_buf *buffer1, t_buf *buffer2)
{
	buffer1->data = NULL;
	buffer1->size = 0;
	buffer2->data = NULL;
	buffer2->size = 0;
}

void	do_stuff(int i, char *av)
{
	t_list		*lex;
	t_list		*label;
	t_buf		buffer_header;
	t_buf		buffer_prog;
	header_t	header;

	buffer_set_zero(&buffer_header, &buffer_prog);
	label = NULL;
//Lexer
	(lex = get_lex(av)) ? 1 : main_error("get_lex error", 1);
	set_lex(lex, &label);
//Parser
	parse(lex, label, &header);
//Affichage && Debug
	i ? ft_lstiter(lex, &debug_lxcontent) : 0;
	i ? ft_lstiter(label, &debug_labelcontent) : 0;
//Error Manager
	check_error(lex);
//Ecriture du player
	write_player(&buffer_prog, lex, label, &header);
	header_to_buffer(&buffer_header, &header);
	write_to_buffer(&buffer_header, buffer_prog.data, buffer_prog.size);
	write_bin(av, &buffer_header);
//Free lst-> Lx && Label
	sp_free(lex, label, &buffer_header, &buffer_prog);
	ft_printf("{green}PROGRAM FINISHED{eoc}\n");
}

void	do_stuff_reverse(char *av)
{
	t_vm_champ	*champ;

	if (!(champ = (t_vm_champ *)malloc(sizeof(t_vm_champ))))
		return ;
	vm_read_champ(av, champ);
	write_player_reverse(av, champ);
}

int		main(int ac, char **av)
{
	int		mode;
	int		i;

	mode = 0;
	i = 1;
	if (ac < 2)
		return (0);
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			ft_printf("Arg %s\n", av[i]);
			if (!ft_strcmp(av[i], "-r"))
				mode = 1;
		}
		else if (mode == 0)
			do_stuff(1, av[i]);
		else if (mode == 1)
			do_stuff_reverse(av[i]);
		++i;
	}
	return (0);
}
