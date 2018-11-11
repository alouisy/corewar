/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:49:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 16:04:24 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** store modification of vm->memory for highlighting in ncurses
** i = tase
*/

void	store_buffer(t_pvm *vm, int i, int color, int cycles)
{
	int				position;

	if (vm->verbose == 1)
	{
		position = i % MEM_SIZE;
		vm->nc.buffer[position] = vm->total_cycles + cycles;
		if (cycles == 50)
		{
			vm->nc.buffer[++position] = vm->total_cycles + cycles;
			vm->nc.buffer[++position] = vm->total_cycles + cycles;
			vm->nc.buffer[++position] = vm->total_cycles + cycles;
			print_4case(vm, i, color);
		}
		else
			print_case(vm->nc.wleft, i, color, vm->memory[position]);
	}
}
