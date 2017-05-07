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

t_gdata			*get_gdata(void)
{
	static t_gdata	*gdata = NULL;

	if (gdata)
		return (gdata);
	gdata = (t_gdata *)malloc(sizeof(t_gdata));
	if (!gdata)
		ft_printf("{red}CRITICAL ERROR\n{eoc}");
	return (gdata);
}