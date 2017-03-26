/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 21:24:08 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/26 14:38:54 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEXER_H

# define __LEXER_H

# include "./../libft/libft.h"
# include <fcntl.h>

const	char	*g_wspace;
const	char	*g_eol;
const	char	*g_delim;

enum {DIRECT, INDIRECT, LABEL, REGISTRE, INSTRUCTION, SEPARATEUR,
	NAME, COMMENT, DIRECTCHAR, LABELREF};

typedef struct	s_lx
{
	int		type;
	int		valeur;
	char	*word;
	size_t	pos[2];
	size_t	index;
}				t_lx;

typedef struct	s_op
{
	char	*name;
	int		nb_param;
	int		type_param[3];
	int		op_code;
	int		nb_cycle;
	char	*cmt;
	int		octet_param;
	int		index;
}				t_op;

void			debug_lxcontent(t_list *lst);

t_list			*get_lex(char *filename);

void			set_lex(t_list *lex);

int				ft_strisnumber(char *str);

#endif
