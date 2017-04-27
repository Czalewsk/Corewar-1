/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 21:24:08 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/27 10:07:37 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEXER_H

# define __LEXER_H

# include "./../libft/libft.h"
# include <fcntl.h>

enum {DIRECT, INDIRECT, LABEL, REGISTRE, INSTRUCTION, SEPARATEUR,
	NAME, COMMENT, DIRECTCHAR, LABELREF, INDIR_LABEL};

typedef struct	s_lx
{
	int			type;
	int			valeur;
	char		*word;
	size_t		pos[2];
	char		*label;
	int			error;
	int			param_error;
}				t_lx;

typedef struct	s_label
{
	char		*name;
	int			octet;
}				t_label;

typedef struct	s_op
{
	char		*name;
	int			nb_p;
	int			type_param[3];
	int			op_code;
	int			nb_cycle;
	char		*cmt;
	int			octet;
	int			index;
}				t_op;

void			debug_lxcontent(t_list *lst);
void			debug_labelcontent(t_list *lst);

t_list			*get_lex(char *filename);

void			set_lex(t_list *lex, t_list **label);

void			del_lex(void *content, size_t size);
void			del_label(void *content, size_t size);


#endif
