/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 00:15:13 by lduval            #+#    #+#             */
/*   Updated: 2017/05/01 11:00:09 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "asm.h"

int		ft_atoi_bigendian(unsigned char *array, int nb_octet)
{
	int j;
	int	i;

	i = 0;
	j = 0;
	while (i < nb_octet)
	{
		j = (j << 8) + array[i];
		i++;
	}
	return (j);
}

void	vm_read_champ_extend(t_buf *buffer, header_t *header)
{
	unsigned char *p;

	if (4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH > buffer->size)
		ft_error(".cor wrong", NULL);
	p = (unsigned char *)buffer->data;
	header->magic = ft_atoi_bigendian(p, 4);
	ft_memcpy(header->prog_name, p + 4, PROG_NAME_LENGTH);
	header->prog_size = ft_atoi_bigendian(p + 4 + PROG_NAME_LENGTH + 4, 4);
	ft_memcpy(header->comment, p + 4 + PROG_NAME_LENGTH + 4 + 4,
			COMMENT_LENGTH);
	if (header->prog_size != (buffer->size
				- (PROG_NAME_LENGTH + COMMENT_LENGTH + 16)))
		ft_error("Champ size invalid", NULL);
	if (header->prog_size > CHAMP_MAX_SIZE)
		ft_error("Champion too big", NULL);
}

void	vm_read_champ(char *path_champion, t_vm_champ *champ)
{
	int				fd;
	int				ret;
	unsigned char	buf[512];
	t_buf			buffer;

	buffer.data = NULL;
	buffer.size = 0;
	if ((fd = open(path_champion, O_RDONLY)) < 0)
		ft_error("Can't open file", NULL);
	while ((ret = read(fd, buf, 1)) > 0)
	{
		buffer.data = realloc(buffer.data, buffer.size + ret);
		if (buffer.data == NULL)
			ft_error("failed realloc in vm_read_champ function", NULL);
		ft_memcpy(buffer.data + buffer.size, buf, ret);
		buffer.size += ret;
	}
	vm_read_champ_extend(&buffer, &(champ->header));
	champ->prog = ft_memdup(buffer.data +
			(PROG_NAME_LENGTH + COMMENT_LENGTH + 16), champ->header.prog_size);
	close(fd);
	free(buffer.data);
}
