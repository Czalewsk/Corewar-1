/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:45:22 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/04 10:16:53 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list			*lex;
t_list			*label;
t_buf			buffer_header;
t_buf			buffer_prog;

extern	t_list	*g_files;

void			sp_free(t_list *lex, t_list *label, t_buf *buffer1,
		t_buf *buffer2)
{
	if (lex)
		ft_lstdel(&lex, &del_lex);
	if (label)
		ft_lstdel(&label, &del_label);
	if (g_files)
		ft_lstdel(&g_files, &del_g_files);
	if (buffer1->data)
		free(buffer1->data);
	if (buffer2->data)
		free(buffer2->data);
}

void			main_error(char *str, int forcequit)
{
	ft_printf("{red}%s{eoc}\n", str);
	sp_free(lex, label, &buffer_header, &buffer_prog);
	if (forcequit)
		exit(1);
}

void			buffer_init(t_buf *buffer1, t_buf *buffer2,
		header_t *header, char *name)
{
	buffer1->data = NULL;
	buffer1->size = 0;
	buffer2->data = NULL;
	buffer2->size = 0;
	ft_memset(header->comment, 0, COMMENT_LENGTH);
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH);
	ft_strcpy(header->prog_name, "DEFAULT_NAME_");
	ft_strncat(header->prog_name, name, PROG_NAME_LENGTH);
	ft_strcpy(header->comment, "DEFAULT_CMT");
}

void			do_stuff(int i, char *av)
{
	header_t	header;

	buffer_init(&buffer_header, &buffer_prog, &header, av);
	label = NULL;
//Lexer
	if ((lex = get_lex(av)) == NULL)
		return (main_error("get_lex error", 0));
	set_lex(lex, &label);
//Parser
	parse(lex, label, &header);
//Affichage && Debug
	i ? ft_lstiter(lex, &debug_lxcontent) : 0;
	i ? ft_lstiter(label, &debug_labelcontent) : 0;
	i ? ft_lstiter(g_files, &debug_print_line) : 0;
//Error Manager
	if (check_error(lex))
		return (main_error("Error in lexer/parser", 0));
//Ecriture du player
	write_player(&buffer_prog, lex, label, &header);
	header_to_buffer(&buffer_header, &header);
	write_to_buffer(&buffer_header, buffer_prog.data, buffer_prog.size);
	write_bin(av, &buffer_header);
//Free lst-> Lx && Label
	sp_free(lex, label, &buffer_header, &buffer_prog);
}

void			do_stuff_reverse(char *av)
{
	t_vm_champ	*champ;

	if (!(champ = (t_vm_champ *)ft_memalloc(sizeof(t_vm_champ))))
		return ;
	vm_read_champ(av, champ);
	write_player_reverse(av, champ);
}

void			get_arg(int *arg, char *av, int *nb_arg)
{
	if (!ft_strcmp(av, "-d"))
		*arg = *arg | 1;
	else if (!ft_strcmp(av, "-r"))
		*arg =* arg | 2;
	++(*nb_arg);
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
	return (0);
}
