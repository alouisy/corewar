/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/11/09 16:14:23 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** rste a tester:
** 	zjmp
**  les cas ou l'opc est bancal
*/

t_op	g_op_tab[17] =
{
	{0, 0, {0}, 0, 2, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0}, //ok
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},//ok
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},//ok
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},//ok
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},//ok
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,//ok
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,//devrait etre aussi ok
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,//devrait etre aussi ok
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1}, //a tester!!!!
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, //ok
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, //semble ok, test pas terrible
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1}, //semble ok, a test avec la vm de zaz
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0}, //ok
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, //ok
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},//semble ok, a test avec la vm de zaz
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0} //ok
};
