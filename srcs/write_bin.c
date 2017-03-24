/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:21:45 by xesnault          #+#    #+#             */
/*   Updated: 2017/03/23 15:21:46 by xesnault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		write_bin(int fd, t_buf *buffer)
{
	return (write(fd, buffer->data, buffer->size));
}

int		write_to_buffer(t_buf *buffer, t_buf *to_add)
{
	buffer->data = realloc(buffer->data, buffer->size + to_add->size);
	if (buffer->data == NULL)
		return (0);
	ft_memcpy(buffer->data + buffer->size, to_add->data, to_add->size);
	return (1);
}