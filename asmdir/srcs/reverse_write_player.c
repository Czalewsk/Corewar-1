/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/05/01 11:11:50 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern	t_op	g_op_tab[];

static	char	*r_parse_param(unsigned char *prog,
	unsigned int *i, unsigned char codage, t_op *op)
{
	int		j;
	char	*text;
	int		value;

	j = 0;
	text = ft_strdup(" ");
	while (j < op->nb_p)
	{
		if (j != 0)
			text = ft_strjoin_free(text, 1, ", ", 0);
		text = ft_strjoin_free(text, 1, r_get_prefix(codage, j), 1);
		value = ft_atoi_bigendian(prog + *i, r_get_nb_octet(codage, j, op));
		if (r_get_nb_octet(codage, j, op) == 1)
			text = ft_strjoin_free(text, 1, ft_itoa(value), 1);
		else if (r_get_nb_octet(codage, j, op) == 2)
			text = ft_strjoin_free(text, 1, ft_itoa((short int)value), 1);
		else if (r_get_nb_octet(codage, j, op) == 4)
			text = ft_strjoin_free(text, 1, ft_itoa(value), 1);
		*i = *i + r_get_nb_octet(codage, j, op);
		++j;
	}
	return (text);
}

static	int		r_parse_instruction(unsigned char *prog,
	unsigned int *i, char **text)
{
	int				j;
	unsigned char	codage;
	char			*text_param;

	j = 0;
	codage = 0;
	while (g_op_tab[j].name)
	{
		if (prog[*i] == g_op_tab[j].op_code)
		{
			*text = ft_strjoin_free(*text, 1, g_op_tab[j].name, 0);
			if (g_op_tab[j].octet && (++(*i)))
				codage = prog[*i];
			++(*i);
			text_param = r_parse_param(prog, i, codage, g_op_tab + j);
			*text = ft_strjoin_free(*text, 1, text_param, 1);
			*text = ft_strjoin_free(*text, 1, "\n", 0);
			return (1);
		}
		++j;
	}
	return (0);
}

static	char	*header_to_str(t_vm_champ *champ)
{
	char	*text;

	text = "# ";
	text = ft_strjoin_free(text, 0,
		ft_itoa_base(champ->header.magic, "0123456789abcdef"), 1);
	text = ft_strjoin_free(text, 1, "\n.name \"", 0);
	text = ft_strjoin_free(text, 1, champ->header.prog_name, 0);
	text = ft_strjoin_free(text, 1, "\"\n.comment \"", 0);
	text = ft_strjoin_free(text, 1, champ->header.comment, 0);
	text = ft_strjoin_free(text, 1, "\"\n\n", 0);
	return (text);
}

static	void	prog_to_str(char **text, t_vm_champ *champ)
{
	unsigned int	i;

	i = 0;
	while (i < champ->header.prog_size)
	{
		if (!r_parse_instruction(champ->prog, &i, text))
		{
			ft_printf("{red}Error: Unknown instruction {%.2x} at byte\
					%d{eoc}\n",
				champ->prog[i], i);
			return ;
		}
	}
}

void			write_player_reverse(char *av, t_vm_champ *champ)
{
	char	*text;

	text = NULL;
	text = header_to_str(champ);
	prog_to_str(&text, champ);
	ft_printf("%s\n", text);
	if (text)
	{
		r_write_to_file(av, text);
		free(text);
	}
	else
		ft_printf("{red}Can't write the content{eoc}\n");
}
