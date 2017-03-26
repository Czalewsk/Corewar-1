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

int		write_to_buffer(t_buf *buffer, void *data, size_t size)
{
	buffer->data = realloc(buffer->data, buffer->size + size);
	if (buffer->data == NULL)
		return (0);
	ft_memcpy(buffer->data + buffer->size, data, size);
	buffer->size += size;
	return (1);
}

void		header_to_buffer(t_buf *buffer, header_t *header)
{
	unsigned int	idk;

	idk = 0;
	if (ft_strlen(header->prog_name) > PROG_NAME_LENGTH)
		ft_printf("[warning] Name too long");
	if (ft_strlen(header->comment) > COMMENT_LENGTH)
		ft_printf("[warning] Comment too long");
	if (!write_to_buffer(buffer, &(header->magic), sizeof(unsigned int)))
		ft_printf("write magic error\n");
	if (!write_to_buffer(buffer, header->prog_name, PROG_NAME_LENGTH))
		ft_printf("write prog name error\n");
	if (!write_to_buffer(buffer, &idk, sizeof(unsigned int)))
		ft_printf("write prog size error\n");
	if (!write_to_buffer(buffer, &(header->prog_size), sizeof(unsigned int)))
		ft_printf("write prog size error\n");
	if (!write_to_buffer(buffer, header->comment, COMMENT_LENGTH))
		ft_printf("write comment error\n");

}
