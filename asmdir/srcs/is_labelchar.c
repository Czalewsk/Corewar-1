/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_labelchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 09:02:20 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/05 16:31:23 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_labelchar(char *str)
{
	while (*str)
		if (!ft_strchr(LABEL_CHARS, *str++))
			return (0);
	return (1);
}

int		is_label_declaration(char *str)
{
	if (!str || !(*str))
		return (0);
	while (*(str + 1))
		str++;
	return (*str == ':' ? 1 : 0);
}

int		check_gramm(int index, char *str)
{
	if (gramm[index].format)
		return ((ft_strcmp(gramm[index].format, str)) ? 0 : 1);
	if (gramm[index].c && gramm[index].c != str[0])
			return (0);
	if (!gramm[index].f && !str[1])
		return (1);
	else if (gramm[index].f && gramm[index].f(str))
		return (1);
	return (0);
}