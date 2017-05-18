/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xesnault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:23:30 by xesnault          #+#    #+#             */
/*   Updated: 2017/05/02 09:36:38 by czalewsk         ###   ########.fr       */
/*   Updated: 2017/04/16 20:49:11 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASM_H

# define __ASM_H

# include "libft.h"
# include "op.h"
# include "lexer.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_buf
{
	void			*data;
	size_t			size;
}					t_buf;

typedef struct      s_tab_error
{
	int				code;
	char			*msg;
	int				nb_arg;
	int				warning;
}					t_tab_error;

typedef struct		s_vm_champ
{
	int				isalive;
	char			*name;
	header_t		header;
	int				num;
	unsigned char	*prog;
	//	t_vm_p *proc;
}					t_vm_champ;

typedef struct		s_gdata
{
	t_list			*lex;
	t_list			*label;
	t_buf			buffer_header;
	t_buf			buffer_prog;
	t_list			*g_files;
}					t_gdata;

int			ft_atoi_bigendian(unsigned char *array, int nb_octet);

void		write_player_reverse(char *av, t_vm_champ *champ);

void        vm_read_champ(char *champ_name,t_vm_champ *data);

void		parse(t_list *list_lex, t_list *label, header_t *header);

int			write_bin(char *filename, t_buf *buffer);

int			write_to_buffer(t_buf *buffer, void *data, size_t size);

void		header_to_buffer(t_buf *buffer, header_t *header);

t_op		*get_instruction(t_lx *lx);

int			is_ref(t_lx *lx, int ref);

int			get_line(t_lx *lx);

t_lx		*get_next_lx(t_list *list_lex);

t_list		*get_next_lst(t_list *list_lex);

t_list		*get_next_field(t_list *list_lex);

int			check_label_chars(t_list *lst);

int			arg_isvalid(t_list **list_lex, t_lx *lx, t_op *op, t_list *label);

char		get_arg_type(int type);

void		check_name_and_cmt(t_list **lst, header_t *header);

void		write_player(t_buf *buffer, t_list *list_lex, t_list *label,
		header_t *header);

int			is_label(char *word);

int			is_direct(t_list *lst);

int			is_indirect(t_list *lst);

int			write_bigendian(t_buf *buffer, int nbr, size_t nb_octet);

t_label		*get_label(t_list *list_label, t_lx *lx);

int			parse_label(t_lx *lx, t_list *lst_lbl);

t_lx		*get_lx_by_type(t_list *list_lex, int type);

void		fill_header(header_t *header, t_list *list_lex, t_buf *buffer);

void		param_to_buffer(t_buf *buffer, t_list **list_lex,
		t_op *op, t_list *list_label);

void		set_codage(unsigned char *codage, t_list *list_lex, t_op *op);

void		add_label(t_lx *lx, t_list **label);

void		main_error(char *str, int forcequit);

int			check_error(t_list *curs);

int			check_sep(t_list *curs, t_lx *lx);

int			count_param(t_list *lst, t_lx *lx, size_t line);

char		*transform_filename(char *filename, char *extension);

int			r_get_nb_octet(unsigned char codage, int i, t_op *op);

char		*r_get_prefix(unsigned char codage, int i);

int			r_write_to_file(char *filename, char *content);

void		underline_error(t_lx *lx, t_list *curs, t_gdata *gdata);

void		debug_print_line(t_list *lst);

void		del_g_files(void *content, size_t size);

void		get_arg(int *arg, char *av, int *nb_arg);

t_gdata		*get_gdata(void);

int			is_instruction(t_lx *lx);

void		sp_free(void);

#endif
