/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/04/16 16:12:49 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tab_error		g_tab_error[17] =
{
	{1, "Syntax error", 0},
	{2, "Label undefined", 0},
	{3, "No such register", 0},
	{4, "Wrong value", 0},
	{5, "Unknown instruction", 0},
	{6, "Invalid argument, got %s expected %s", 2},
	{7, "Instruction %s has %d argument(s) expected %d", 3},
	{8, "Label already defined", 0},
	{9, "Missing quote", 0},
	{10, "Wrong character in label", 0},
	{11, "Name too long", 0},
	{12, "Comment too long", 0},
	{13, "Prog too big", 0},
	{14, "Missing name", 0},
	{15, "Missing comment", 0},
	{17, NULL, 0}
};
