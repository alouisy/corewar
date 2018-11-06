/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 16:50:38 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** insert each champion's programme in left panel
*/

/*
** first print of map with "00" only
*/

void	print_map(t_pvm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		wattron(vm->nc.wleft, COLOR_PAIR(vm->mem_color[i]));
		if (vm->memory[i] == 0)
			mvwprintw(vm->nc.wleft, 1 + i / 64, 1 + (i % 64) * 3, "00 ");
		else
			mvwprintw(vm->nc.wleft, 1 + i / 64, 1 + (i % 64) * 3, "%.2hhx", vm->memory[i]);
		wattroff(vm->nc.wleft, COLOR_PAIR(vm->mem_color[i]));
		i++;
	}
}
