/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 00:15:13 by lduval            #+#    #+#             */
/*   Updated: 2017/04/19 06:08:16 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include "vm_header.h"

int		ft_atoi_bigendian(unsigned char *array, int nb_octet)
{
	int j;
	int	i;

	i = 0;
	j = 0;
	while (i  < nb_octet)
	{
		j = (j << 8) + array[i];
		i++;
	}
	return (j);
}

void	vm_read_champ_extend(t_buf *buffer, header_t *header)
{
	unsigned char *p;
	int i;

	if (4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH > buffer->size)
		ft_error(".cor wrong", &vm_free_all);
	p = (unsigned char *)buffer->data;
	i = 4;
	header->magic = ft_atoi_bigendian(p, 4);
	//ft_memcpy(header->prog_name, p + i, PROG_NAME_LENGTH);
	while (i < PROG_NAME_LENGTH + 1 && *(p + i))
	{
		header->prog_name[i] = *(p + i);
		i++;
	}
	*(p + i) !=  0 ? ft_error("i never segfault the first night", &vm_free_all) : NULL;
	while (*(p + i) == 0 && i < buffer->size)
		i++;
	header->prog_size = ft_atoi_bigendian(p + i, 4);
	i += 8;
	//ft_memcpy(header->comment, p + 4 + PROG_NAME_LENGTH + 4 + 4, COMMENT_LENGTH);
	while (i < COMMENT_LENGTH + 1 && *(p + i))
	{
		header->comment[i] = *(p + i);
		i++;
	}
	*(p + i) !=  0 ? ft_error("i never segfault the first night", &vm_free_all) : NULL;
	while (*(p + i) == 0 && i < buffer->size)
		i++;
	ft_printf("%x, %s, %u, %s" ,header->magic, header->prog_name, header->comment, header->comment);
}                                       
void    vm_read_champ(char *path_champion, t_vm_champ *champ)
{
	int				fd;
	int				ret;
	int 			i;
	unsigned char	buf[512];
	t_buf			buffer;
	
	buffer.data = NULL;
	buffer.size = 0;
	i = 0;
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
}

