/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:49:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 17:51:29 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** update highlight in left panel of ncurses
*/

void	update_buffer(t_pvm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->total_cycles == vm->nc.buffer[i])
			print_case(vm->nc.wleft, i, vm->mem_color[i], vm->memory[i]);
		i++;
	}
}
