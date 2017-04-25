/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/04/25 11:22:22 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tab_error		g_tab_error[20] =
{
	{"Syntax error", 0, 0},
	{"Label undefined", 0, 0},
	{"No such register", 0, 0},
	{"Wrong value", 0, 1},
	{"Unknown instruction", 0, 0},
	{"Invalid argument, got %s expected %s", 2, 0},
	{"Instruction %s has %d argument(s) expected %d", 3, 0},
	{"Label already defined", 0, 0},
	{"Missing quote", 0, 0},
	{"Wrong character in label", 0, 0},
	{"Name too long", 0, 1}, //Warning
	{"Comment too long", 0, 1}, // Warning
	{"Prog too big", 0, 0},
	{"Missing name", 0, 1}, //Warning or error
	{"Missing comment", 0, 1}, // Warning or error
	{"Expected statement", 0, 0},
	{"Missing label name", 0, 0},
	{"Missing separator between arguments", 0, 0},
	{"Value %s is too large to be represented in integer", 0, 1},
	{NULL, 0, 0}
};
