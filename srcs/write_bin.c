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

int		write_bin(char *filename, t_buf *buffer)
{
	int	fd;
	int	ret;

	fd = open(filename, O_WRONLY | O_CREAT, 0664);
	if (fd == -1)
		return (0);
	ret = write(fd, buffer->data, buffer->size);
	close(fd);
	return (ret);
}

int		write_to_buffer(t_buf *buffer, t_buf *to_add)
{
	buffer->data = realloc(buffer->data, buffer->size + to_add->size);
	if (buffer->data == NULL)
		return (0);
	ft_memcpy(buffer->data + buffer->size, to_add->data, to_add->size);
	buffer->size += to_add->size;
	return (1);
}

void		header_to_buffer(t_buf *buffer, header_t *header)
{
	t_buf	to_add;

	if (ft_strlen(header->prog_name) > PROG_NAME_LENGTH)
		ft_printf("[warning] Name too long");
	if (ft_strlen(header->comment) > COMMENT_LENGTH)
		ft_printf("[warning] Comment too long");
	to_add.data = header->prog_name;
	to_add.size = PROG_NAME_LENGTH;
	if (!write_to_buffer(buffer, &to_add))
		ft_printf("write name error\n");
	to_add.data = header->comment;
	to_add.size = COMMENT_LENGTH;
	if (!write_to_buffer(buffer, &to_add))
		ft_printf("write comment error\n");

}
