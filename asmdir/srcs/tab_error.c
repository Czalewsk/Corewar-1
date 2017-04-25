/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/04/25 12:18:39 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tab_error		g_tab_error[20] =
{
	{1, "Syntax error", 0, 0},
	{2, "Label undefined", 0, 0},
	{3, "No such register", 0, 0},
	{4, "Wrong value", 0, 1},
	{5, "Unknown instruction", 0, 0},
	{6, "Invalid argument, got %s expected %s", 2, 0},
	{7, "Instruction %s has %d argument(s) expected %d", 3, 0},
	{8, "Label already defined", 0, 0},
	{9, "Missing quote", 0, 0},
	{10, "Wrong character in label", 0, 0},
	{11, "Name too long", 0, 1}, //Warning
	{12, "Comment too long", 0, 1}, // Warning
	{19, "Prog too big", 0, 0},
	{20, "Missing name", 0, 1}, //Warning or error
	{21, "Missing comment", 0, 1}, // Warning or error
	{22, "Expected statement", 0, 0},
	{23, "Missing label name", 0, 0},
	{24, "Missing separator between arguments", 0, 0},
	{25, "Value %s is too large to be represented in integer", 0, 1},
	{NULL, 0, 0}
};
