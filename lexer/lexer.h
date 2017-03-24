/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 21:24:08 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/23 23:50:38 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEXER_H

# define __LEXER_H

# include "./../libft/libft.h"
# include <fcntl.h>

typedef struct	s_lx
{
	int		type;
	int		valeur;
	char	*word;
	size_t	pos[2];
	size_t	index;
}				t_lx;

void			debug_lxcontent(t_list *lst);

t_list			*get_lex(char *filename);

#endif
