/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_say.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 12:20:19 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 15:16:33 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"
#include <signal.h>

void	ft_say(char *input)
{
	char *s;
	char *l;

	s = (char *)malloc(ft_strlen("say ") + 1);
	s = ft_strcpy(s, "say ");
	l = ft_strjoin(s, input);
	system(l);
	free(s);
	free(l);
}

void	ft_afplay(char *input)
{
	static pid_t	sound_process = -2;
	char			**inp;
	int				i;

	inp = ft_strsplit(input, ' ');
	if (sound_process != -2)
		kill(sound_process, 9);
	if ((sound_process = fork()) == 0)
	{
		execve("/usr/bin/afplay", inp, NULL);
		exit(0);
	}
	i  = 0;

}
