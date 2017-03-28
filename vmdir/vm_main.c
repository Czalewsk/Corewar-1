/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 22:48:45 by lduval            #+#    #+#             */
/*   Updated: 2017/03/28 01:47:39 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_header.h"

int	main(int argc, char **argv)
{
//	init_structs();
	/*
	** initialise l'ensemble des structurs singletons ,
	** utilis�es tout aux long du programme.
	*/ 
	vm_pars_param(argc, argv);
	/*
	 * V�rifie si le nombre de parametre est bon,
	 * Si il est ,la foncton verifie si les diff�rents param�tres,
	 * sont coh�rents. Et remplis les singletons ad�cuat(si besoin)
	 * verifie si les fichier players sp�cifi� existe. Return (0) si tout s'est bien pass�
	*/ 
	//if (pars_files())
	//	ft_error(ERR_READ, &free_all);
	/*
	 * Pars les fichier de champion,  retrun (0) si tout s'est bien pass�, -1 si il y a une erreur pendant la lecture ou si un champion est trop gros.
	 */ 
	//init_map();
	/*
	 *
	 * Alloue l'espace m�moire pour la partie. initialise la partie graphique si cela � �tait sp�cifi� dans les parametre
	 */ 
	//init_champ()
	/*
	 * place les champion sur la carte
	 */
	//fight()
	/*
	 * execute la partie.
	 * 
	 */
	//free_all();
	/*
	 * desalloue toute la m�moire restante.
	 */ 
	return (EXIT_SUCCESS);
}
