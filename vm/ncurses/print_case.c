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

void	print_case(WINDOW *win, int pos, int color, unsigned char c)
{
	wattron(win, COLOR_PAIR(color));
	mvwprintw(win, (pos / 64) % 64 + 1, (pos % 64) * 3 + 1, "%.2hhx", c);
	wattroff(win, COLOR_PAIR(color));
}

void	print_4case(t_pvm *vm, int pos, int color)
{
	int i;

	i = 0;
	while (i < 4)
	{
		print_case(vm->nc.wleft, pos + i, color, vm->memory[(pos + i) % MEM_SIZE]);
		i++;
	}
}
