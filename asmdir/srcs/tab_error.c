/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/05/23 04:23:11 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tab_error		g_tab_error[50] =
{
	{1, "Syntax error", 0, 0},
	{2, "Label undefined", 0, 0},
	{3, "Register %s don\'t exist", 1, 1},
	{4, "Wrong value", 0, 0},
	{5, "Unknown instruction", 0, 0},
	{6, "Invalid argument, got {U}%s{eoc} expected {U}%s{eoc}", 2, 0},
	{7, "Instruction {U}%s{eoc} has {U}%s{eoc} argument(s) expected {U}%s{eoc}"
		, 3, 0},
	{8, "Label already defined", 0, 0},
	{9, "Missing openning quote", 0, 0},
	{10, "Wrong character in label", 0, 0},
	{11, "Name too long", 0, 1},
	{12, "Comment too long", 0, 1},
	{13, "Prog too big", 0, 0},
	{14, "Missing name", 0, 1},
	{15, "Missing comment", 0, 1},
	{16, "Expected statement", 0, 0},
	{17, "Missing label name", 0, 0},
	{18, "Missing separator between arguments", 0, 0},
	{19, "Value %s is too large to be represented in integer", 1, 1},
	{20, "Instruction {U}%s{eoc} is unknown", 1, 0},
	{21, "White space between LABEL_CHAR and label", 0, 0},
	{22, "Separator \"%s\" at the end of the line", 1, 0},
	{23, "Multiple label define on the same line", 0, 0},
	{24, "Missing quote", 0, 0},
	{25, "No program", 0, 0},
	{26, "Not defined", 0, 0},
	{27, "Not defined", 0, 0},
	{28, "Not defined", 0, 0},
	{29, "Missing name and comment", 0, 1},
	{30, "Not defined", 0, 0},
	{0, NULL, 0, 0}
};
