/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 00:15:13 by lduval            #+#    #+#             */
/*   Updated: 2017/05/03 11:55:49 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include "vm_header.h"

void	vm_read_champ_extend(t_buf *buffer, t_header *header)
{
	unsigned char *p;

	if (4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH > buffer->size)
		ft_error(".cor wrong", &vm_free_all);
	p = (unsigned char *)buffer->data;
	header->magic = ft_atoi_bigendian(p, 4);
	ft_memcpy(header->prog_name, p + 4, PROG_NAME_LENGTH);
	header->prog_size = ft_atoi_bigendian(p + 4 + PROG_NAME_LENGTH + 4, 4);
	ft_memcpy(header->comment, p + 4 + PROG_NAME_LENGTH + 4 + 4, COMMENT_LENGTH);
	ft_printf("%x, %s, %u, %s\n" ,header->magic, header->prog_name, header->prog_size, header->comment);
	ft_printf("%u\n" ,buffer->size - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16));
	if (header->prog_size != (buffer->size - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16)))
        ft_error("Champ size invalid", &vm_free_all);
    if (header->prog_size > CHAMP_MAX_SIZE)
        ft_error("Champion too big", &vm_free_all);
}

void    vm_read_champ(char *path_champion, t_vm_champ *champ)
{
	int				fd;
	int				ret;
	unsigned char	buf[512];
	t_buf			buffer;

	buffer.data = NULL;
	buffer.size = 0;
	if ((fd = open(path_champion, O_RDONLY)) < 0)
		ft_error("Can't open file", &vm_free_all);
	while ((ret = read(fd, buf, 1)) > 0)
	{
		buffer.data = realloc(buffer.data, buffer.size + ret);
		if (buffer.data == NULL)
			ft_error("failed realloc in vm_read_champ function", &vm_free_all);
		ft_memcpy(buffer.data + buffer.size, buf, ret);
		buffer.size += ret;
	}
	vm_read_champ_extend(&buffer, &(champ->header));
    champ->prog = ft_memdup(buffer.data + (PROG_NAME_LENGTH + COMMENT_LENGTH + 16), champ->header.prog_size);
    close(fd);
    free(buffer.data);
}
