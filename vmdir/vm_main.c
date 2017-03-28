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
	** utilisées tout aux long du programme.
	*/ 
	vm_pars_param(argc, argv);
	/*
	 * Vérifie si le nombre de parametre est bon,
	 * Si il est ,la foncton verifie si les différents paramètres,
	 * sont cohérents. Et remplis les singletons adécuat(si besoin)
	 * verifie si les fichier players spécifié existe. Return (0) si tout s'est bien passé
	*/ 
	//if (pars_files())
	//	ft_error(ERR_READ, &free_all);
	/*
	 * Pars les fichier de champion,  retrun (0) si tout s'est bien passé, -1 si il y a une erreur pendant la lecture ou si un champion est trop gros.
	 */ 
	//init_map();
	/*
	 *
	 * Alloue l'espace mémoire pour la partie. initialise la partie graphique si cela à était spécifié dans les parametre
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
	 * desalloue toute la mémoire restante.
	 */ 
	return (EXIT_SUCCESS);
}
