/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:04:33 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline void print_map(t_pvm *vm)
{
	unsigned int 	i;

	vm->nc.wleft = subwin(stdscr, LINES,  15 * COLS / 20, 0, 0);
	vm->nc.wright = subwin(stdscr, LINES, 5 * COLS / 20, 0, 15 * COLS / 20);
	box(vm->nc.wleft, ACS_VLINE, ACS_HLINE);
	box(vm->nc.wright, ACS_VLINE, ACS_HLINE);
	i = 0;
	while (i < MEM_SIZE)
	{
		mvwprintw(vm->nc.wleft, i / 64 + 1, (i % 64) * 3 + 1, "00");
		if ((i % 64) == 0)
			mvwprintw(vm->nc.wleft, i / 64 + 2, (i % 64) * 3 + 1, " ");
		i++;
	}
}
