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

t_op	g_op_tab[17] =
{
	{0, 0, {0}, 0, 2, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0}, //n'accepte pas les nombres sup à 2^31
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0}, //ok
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0}, //ok
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0}, //ok
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0}, //ok
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1}, //check carry à faire
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, //des différences surtout avec les indirectes, et peut etre avec le modulo IDX_MOD
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, //pas mal de différentces, probablement meme soucis que ldi et lldi
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1}, //a test
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0}, //ok
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, //des différences avec les indirectes
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},//a test
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0} //ok
};
