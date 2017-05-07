/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:07:23 by xesnault          #+#    #+#             */
/*   Updated: 2017/05/01 11:02:49 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

int			r_get_nb_octet(unsigned char codage, int i, t_op *op)
{
	if (codage == 0 && op->index)
		return (2);
	else if (codage == 0)
		return (4);
	else if (((codage >> (6 - i * 2)) & 0x03) == REG_CODE)
		return (1);
	else if (((codage >> (6 - i * 2)) & 0x03) == DIR_CODE && op->index)
		return (2);
	else if (((codage >> (6 - i * 2)) & 0x03) == DIR_CODE)
		return (4);
	else if (((codage >> (6 - i * 2)) & 0x03) == IND_CODE)
		return (2);
	return (0);
}

char		*r_get_prefix(unsigned char codage, int i)
{
	char	*str;

	str = NULL;
	if (((codage >> (6 - i * 2)) & 0x03) == REG_CODE)
		str = ft_strdup("r");
	else if (((codage >> (6 - i * 2)) & 0x03) == DIR_CODE || codage == 0)
		str = ft_strdup("%");
	else if (((codage >> (6 - i * 2)) & 0x03) == IND_CODE)
		str = ft_strdup("");
	if (str)
		return (str);
	return (ft_strdup("ERROR"));
}

int			r_write_to_file(char *filename, char *content)
{
	int	fd;
	int	ret;

	filename = ft_cfextension(filename, "CX.s");
	if (!filename)
		filename = ft_strdup("NameError.s");
	ft_printf("The new filename is {cyan}%s{eoc}\n", filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (0);
	ret = write(fd, content, ft_strlen(content));
	close(fd);
	free(filename);
	return (ret);
}
