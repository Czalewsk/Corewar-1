/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 09:15:40 by czalewsk          #+#    #+#             */
/*   Updated: 2017/02/10 15:42:28 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isint(char *nb)
{
	intmax_t	nbr;
	int			n;
	int			nb_len;

	n = 0;
	nb_len = 0;
	while (nb[n] == ' ')
		n++;
	if (nb[n] != '+' || nb[n] != '-')
		n++;
	while (nb[n + nb_len] && ft_isdigit(nb[nb_len + n]) && nb[n + nb_len] != 48)
		nb_len++;
	if (nb_len > 10)
		return (0);
	while (nb[n])
		if (!ft_isdigit(nb[n++]))
			return (0);
	nbr = ft_atoi(nb);
	if (nbr < INT_MIN || nbr > INT_MAX)
		return (0);
	return (1);
}
/*
**	intmax_t	nbr;
**	int			i;
**	char		*nb_cp;
**	int			len;
**
**	len = 0;
**	i = 0;
**	while (nb[i] && nb[i] == ' ')
**		i++;
**	if (nb[i] == '+')
**		i++;
**	else if (nb[i] == '-' && ft_isdigit(nb[i + 1]))
**		len++;
**	while (nb[i + len] && ft_isdigit(nb[i + len]))
**		len++;
**	if (len == 0)
**		return (0);
**	nbr = ft_atoi(nb + i);
**	nb_cp = ft_itoa((int)nbr);
**	if (!ft_strncmp(nb + i, nb_cp, len))
**		i = -1;
**	else
**		i = -2;
**	ft_strdel(&nb_cp);
**	return ((i == -1) ? 1 : 0);
*/
