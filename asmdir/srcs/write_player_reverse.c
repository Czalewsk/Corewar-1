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

void		write_player_reverse(char *av, t_vm_champ *champ)
{
	char	*text;
	(void)av;
	(void)champ;

	text = "// ";
	text = ft_strjoin_free(text, 0, ft_itoa_base(champ->header.magic, "0123456789abcdef"), 1);
	text = ft_strjoin_free(text, 1, "\n", 0);
	text = ft_strjoin_free(text, 1, champ->header.prog_name, 0);
	ft_printf("%s\n", text);
}
