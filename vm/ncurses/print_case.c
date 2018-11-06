/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 16:17:52 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** print one case
*/

void	print_case(WINDOW *win, int pos, unsigned char c)
{
	if (c == 0)
	{
		mvwprintw(win, (pos) / 64 + 1, ((pos) % 64) * 3 + 1, "00");
	}
	else
		mvwprintw(win, (pos) / 64 + 1, ((pos) % 64) * 3 + 1, "%.2hhx", c);
}

void	print_4case(t_pvm *vm, int pos, int color)
{
	int i;

	i = 0;
	wattron(vm->nc.wleft, COLOR_PAIR(color));
	while (i < 4)
	{
		if (vm->memory[i] == 0)
			mvwprintw(vm->nc.wleft, ((pos + i) / 64 + 1) % 64, ((pos + i) % 64) * 3 + 1, "00");
		else
			mvwprintw(vm->nc.wleft, ((pos + i) / 64 + 1) % 64, ((pos + i) % 64) * 3 + 1, "%.2hhx", vm->memory[pos]);
		i++;
	}
	wattroff(vm->nc.wleft, COLOR_PAIR(color));
}
