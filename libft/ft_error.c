/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 11:02:05 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/13 08:45:10 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(int fd, char *msg, void *content, void (*del)(void *))
{
	ft_putstr_fd("ERROR", fd);
	if (msg)
		ft_printf(" : %s", msg);
	write(fd, "\n", 1);
	if (content && del)
		del(content);
	exit(0);
}
