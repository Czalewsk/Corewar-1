/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:45:22 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/23 09:45:56 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			main_error(char *str, int forcequit)
{
	ft_printf("{red}%s{eoc}\n", str);
	sp_free();
	if (forcequit)
		exit(1);
}

void			buffer_init(header_t *header, char *name)
{
	t_gdata	*gdata;

	gdata = get_gdata();
	gdata->label = NULL;
	gdata->g_files = NULL;
	gdata->buffer_header.data = NULL;
	gdata->buffer_header.size = 0;
	gdata->buffer_prog.data = NULL;
	gdata->buffer_prog.size = 0;
	ft_memset(header->comment, 0, COMMENT_LENGTH);
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH);
	ft_strcpy(header->prog_name, "DEFAULT_NAME_");
	ft_strncat(header->prog_name, name, PROG_NAME_LENGTH);
	ft_strcpy(header->comment, "DEFAULT_CMT");
}

void			do_stuff(int i, char *av)
{
	header_t	header;
	t_gdata		*gdata;

	gdata = get_gdata();
	buffer_init(&header, av);
	if ((gdata->lex = get_lex(av)) == NULL)
		return (main_error("get_lex error", 0));
	set_lex(gdata->lex, &(gdata->label));
	parse(gdata->lex, gdata->label, &header);
	i ? ft_lstiter(gdata->lex, &debug_lxcontent) : 0;
	i ? ft_lstiter(gdata->label, &debug_labelcontent) : 0;
	i ? ft_lstiter(gdata->g_files, &debug_print_line) : 0;
	if (check_error(gdata->lex))
		return (main_error("Error in lexer/parser", 0));
	write_player(&(gdata->buffer_prog), gdata->lex, gdata->label, &header);
	header_to_buffer(&(gdata->buffer_header), &header);
	write_to_buffer(&(gdata->buffer_header), gdata->buffer_prog.data,
		gdata->buffer_prog.size);
	write_bin(av, &(gdata->buffer_header));
	sp_free();
}

void			do_stuff_reverse(char *av)
{
	t_vm_champ	*champ;

	if (!(champ = (t_vm_champ *)ft_memalloc(sizeof(t_vm_champ))))
		return ;
	vm_read_champ(av, champ);
	write_player_reverse(av, champ);
}

int				main(int ac, char **av)
{
	int		arg;
	int		i;
	int		nb_arg;

	arg = 0;
	i = 0;
	nb_arg = 0;
	while (++i < ac && ac > 1 && av[i][0] == '-')
		get_arg(&arg, av[i], &nb_arg);
	--i;
	while (++i < ac && ac > 1)
	{
		ft_printf("[%d/%d] %s:\n", i - nb_arg, (ac - 1) - nb_arg, av[i]);
		if (!(arg & 2))
			do_stuff(arg & 1, av[i]);
		else if (arg & 2)
			do_stuff_reverse(av[i]);
	}
	free(get_gdata());
	return (0);
}
