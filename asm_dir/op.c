/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcugni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 23:41:42 by zcugni            #+#    #+#             */
/*   Updated: 2018/11/05 23:41:42 by zcugni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	g_op_tab[16] =
{
	{"aff", 1, {T_REG}, 16, 1, DIR_SIZE},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, DIR_SIZE},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 1, DIR_SIZE},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, DIR_SIZE},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 2},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 
																DIR_SIZE},
	{"live", 1, {T_DIR}, 1, 0, DIR_SIZE},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1,
																DIR_SIZE},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, DIR_SIZE},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 2},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, DIR_SIZE},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 1, DIR_SIZE},
	{"lfork", 1, {T_DIR}, 15, 0, 2},
	{"fork", 1, {T_DIR}, 12, 0, 2},
	{"zjmp", 1, {T_DIR}, 9, 0, 2}
};
