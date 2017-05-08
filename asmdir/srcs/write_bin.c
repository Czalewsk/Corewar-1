/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:21:45 by xesnault          #+#    #+#             */
/*   Updated: 2017/05/07 16:30:32 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*transform_filename(char *filename, char *extension)
{
	char	*tmp;
	char	*old_filename;
	char	*new_filename;

	old_filename = ft_strnew(ft_strlen(filename) + 1);
	new_filename = ft_strnew(ft_strlen(filename) + 10);
	if (!old_filename || !new_filename)
	{
		ft_strdel(&old_filename);
		ft_strdel(&new_filename);
		return (NULL);
	}
	ft_strcpy(old_filename, filename);
	tmp = ft_strrchr(old_filename, '.');
	if (!tmp)
	{
		ft_strdel(&old_filename);
		ft_strdel(&new_filename);
		return (NULL);
	}
	*tmp = 0;
	ft_strcpy(new_filename, old_filename);
	ft_strcat(new_filename, extension);
	free(old_filename);
	return (new_filename);
}

int			write_bin(char *filename, t_buf *buffer)
{
	int	fd;
	int	ret;

	filename = ft_cfextension(filename, "CX.cor");
	if (!filename)
		filename = ft_strdup("NameError.cor");
	ft_printf("Writing output program to {cyan}%s{eoc}\n", filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	free(filename);
	if (fd == -1)
		return (0);
	ret = write(fd, buffer->data, buffer->size);
	close(fd);
	return (ret);
}

int			write_to_buffer(t_buf *buffer, void *data, size_t size)
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
	if (!write_bigendian(buffer, header->magic, sizeof(unsigned int)))
		ft_printf("write magic error\n");
	if (!write_to_buffer(buffer, header->prog_name, PROG_NAME_LENGTH))
		ft_printf("write prog name error\n");
	if (!write_to_buffer(buffer, &idk, sizeof(unsigned int)))
		ft_printf("write name null octet error\n");
	if (!write_bigendian(buffer, header->prog_size, sizeof(unsigned int)))
		ft_printf("write prog size error\n");
	if (!write_to_buffer(buffer, header->comment, COMMENT_LENGTH))
		ft_printf("write comment error\n");
	if (!write_to_buffer(buffer, &idk, sizeof(unsigned int)))
		ft_printf("write comment null octet error\n");
}

int			write_bigendian(t_buf *buffer, int nbr, size_t nb_octet)
{
	unsigned char	tmp[4];

	buffer->data = realloc(buffer->data, buffer->size + nb_octet);
	if (buffer->data == NULL)
		return (0);
	tmp[0] = (nbr >> 24) & 0xff;
	tmp[1] = (nbr >> 16) & 0xff;
	tmp[2] = (nbr >> 8) & 0xff;
	tmp[3] = nbr & 0xff;
	ft_memcpy(buffer->data + buffer->size, tmp + (4 - nb_octet), nb_octet);
	buffer->size += nb_octet;
	return (1);
}
