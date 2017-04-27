/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:36:55 by czalewsk          #+#    #+#             */
/*   Updated: 2017/04/27 13:23:24 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

const	char	*g_wspace = " \t";
const	char	*g_eol = "#;\n";
const	char	*g_delim = ":,";
t_list			*g_files;

void			get_end_word(char const *s, size_t *i)
{
	if (s[(*i)] && s[(*i)] == '\"' && ++(*i))
		while (s[(*i)] && s[(*i)] != '\"')
			++(*i);
	if (s[(*i)] && ft_strchr(g_delim, s[(*i)]) && ++(*i))
		return ;
	while (s[(*i)] && !ft_strchr(g_wspace, s[(*i)])
			&& !ft_strchr(g_eol, s[(*i)]) && !ft_strchr(g_delim, s[(*i)]))
	{
		++(*i);
		if (s[*i] == LABEL_CHAR && ++(*i))
			return ;
	}
}

int				get_next_word(char const *s, size_t *i)
{
	while (s[*i] && ft_strchr(g_wspace, s[*i]))
		(*i)++;
	if (!s[*i] || ft_strchr(g_eol, s[*i]))
		return (0);
	return (1);
}

t_lx			*lx_init(char *word, size_t ln, size_t cl)
{
	t_lx		*new;

	if (!word || !(new = (t_lx*)ft_memalloc(sizeof(t_lx))))
		return (NULL);
	new->type = -1;
	new->valeur = -1;
	new->word = word;
	new->pos[0] = ln;
	new->pos[1] = cl;
	return (new);
}

void			fill_lst(t_list **start, char *line, size_t ln)
{
	size_t		beg;
	size_t		end;
	t_lx		*new_lx;

	beg = 0;
	while (get_next_word(line, &beg))
	{
		end = beg;
		get_end_word(line, &end);
		if (end - beg > 0)
		{
			new_lx = lx_init(ft_strsub(line + beg, 0, end - beg), ln, beg);
			new_lx ? ft_lst_pushend(start, ft_lstnew(new_lx, sizeof(t_lx)))
				: NULL;
			ft_memdel((void**)&new_lx);
		}
		beg = end;
	}
}

t_list			*get_lex(char *filename)
{
	int		fd;
	size_t	ln;
	char	*line;
	t_list	*lexem;

	ln = 0;
	line = NULL;
	lexem = NULL;
	g_files = NULL;
	if ((fd = open(filename, O_RDONLY)) <= 0)
	{
		ft_printf("Ceci n'a pas marche (fichier introuvable)\n");
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0 && ++ln)
	{
		fill_lst(&lexem, line, ln);
		ft_lst_pushend(&g_files, ft_lstnew(&line, sizeof(&line)));
	//	ft_strdel(&line);
	}
	ft_lst_pushend(&g_files, ft_lstnew(&line, sizeof(&line)));
//	ft_strdel(&line);
	close(fd);
	return (lexem);
}
