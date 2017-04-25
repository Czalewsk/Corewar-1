/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/04/17 12:47:27 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

static int	get_nb_octet(unsigned char codage, int i, t_op *op)
{

	if (codage == 0 && op->index)
		return (2);
	else if (codage == 0)
		return (4);
	else if (((codage >> (6 - i * 2)) & 0x03) == 1)
		return (1);
	else if (((codage >> (6 - i * 2)) & 0x03) == 2 && op->index)
		return (2);
	else if (((codage >> (6 - i * 2)) & 0x03) == 2)
		return (4);
	else if (((codage >> (6 - i * 2)) & 0x03) == 3)
		return (2);
	return (0);
}

static char	*r_parse_param(unsigned char *prog, unsigned int *i, unsigned char codage, t_op *op)
{
	int 	j;
	char	*text;

	j = 0;
	text = "";
	(void)text;
	while (j < op->nb_p)
	{
		if (get_nb_octet(codage, j, op) == 1)
			ft_printf("arg: %hhd ", ft_atoi_bigendian(prog + *i, get_nb_octet(codage, j, op)));
		else if (get_nb_octet(codage, j, op) == 2)
			ft_printf("arg: %hd ", ft_atoi_bigendian(prog + *i, get_nb_octet(codage, j, op)));
		else if (get_nb_octet(codage, j, op) == 4)
			ft_printf("arg: %d ", ft_atoi_bigendian(prog + *i, get_nb_octet(codage, j, op)));
		*i = *i + get_nb_octet(codage, j, op);
		++j;
	}
	return (NULL);
}

static int	r_parse_instruction(unsigned char *prog, unsigned int *i)
{
	int 			j;
	unsigned char	codage;

	j = 0;
	codage = 0;
	while (g_op_tab[j].name)
	{
		if (prog[*i] == g_op_tab[j].op_code)
		{
			ft_printf("%s ", g_op_tab[j].name);
			if (g_op_tab[j].octet && (++(*i)))
				codage = prog[*i];
			++(*i);
			r_parse_param(prog, i, codage, g_op_tab + j);
			return (1);
		}
		++j;
	}
	return (0);
}

static char	*header_to_str(t_vm_champ *champ)
{
	char	*text;

	text = "# ";
	text = ft_strjoin_free(text, 0, ft_itoa_base(champ->header.magic, "0123456789abcdef"), 1);
	text = ft_strjoin_free(text, 1, "\n.name \"", 0);
	text = ft_strjoin_free(text, 1, champ->header.prog_name, 0);
	text = ft_strjoin_free(text, 1, "\"\n.comment \"", 0);
	text = ft_strjoin_free(text, 1, champ->header.comment, 0);
	text = ft_strjoin_free(text, 1, "\"\n\n", 0);
	return (text);
}
static void	prog_to_str(char **text, t_vm_champ *champ)
{
	unsigned int	i;

	i = 0;
	(void)text;
	while (i < champ->header.prog_size)
	{
		if (!r_parse_instruction(champ->prog, &i))
			ft_printf("%.2x ", champ->prog[i]);
	}
}

void		write_player_reverse(char *av, t_vm_champ *champ)
{
	char	*text;
	(void)av;
	(void)champ;

	text = header_to_str(champ);
	prog_to_str(&text, champ);
	ft_printf("%s\n", text);
}
