/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:33:57 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/28 05:19:24 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *big, const char *little)
{
	char	*tmp;
	int		n;
	int		m;
	int		i;

	i = 0;
	n = ft_strlen(little);
	m = ft_strlen(big);
	tmp = (char *)big + m;
	if (n == 0)
		return ((char*)big);
	while (big <= tmp)
	{
		while (tmp[i] == little[i]){
			if (++i == n)
				return (tmp);
		}
		i = 0;
		tmp--;
	}
	return (NULL);
}
