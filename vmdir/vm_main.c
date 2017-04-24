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

void vm_print_arena(void)
{
    t_vm_data   *dat;
    int         i;
    unsigned char        c;

    dat = get_data();
    i = 0;
    while (i < MEM_SIZE)
    {

        ft_printf("%d: %.2x\n", i ,  dat->arena[i]);
        //ft_printf("%d: %02x\n", i ,  dat->arena[i]);
        i++;
    }
}

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
	 * verifie si les fichier players spécifié existe. Si ils sont correcte :Return (0) si tout s'est bien passé
	*/
	vm_init_arena();
	/*
	 *
	 * Alloue l'espace mémoire pour la partie. initialise la partie graphique si cela à était spécifié dans les parametre, allloue les champion aux bon endroits:
	 *
	 */
	//fight()
	/*
	 * execute la partie.
	 *

	//vm_free_all();
	/*
	 * desalloue toute la mémoire restante.
	 */
	return (EXIT_SUCCESS);
}
