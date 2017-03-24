/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:33:57 by czalewsk          #+#    #+#             */
/*   Updated: 2016/11/08 18:03:56 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		n;
	int		i;

	i = 0;
	n = ft_strlen(little);
	if (n == 0)
		return ((char*)big);
	while (*big)
	{
		while (big[i] == little[i])
			if (++i == n)
				return ((char*)big);
		i = 0;
		big++;
	}
	return (NULL);
}
