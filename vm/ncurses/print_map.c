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
**print vm->memory
*/

void	print_map(t_pvm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->memory[i] != vm->nc.memory[i])
		{
			print_case(vm->nc.wleft, i, vm->mem_color[i], vm->memory[i]);
			vm->nc.memory[i] = vm->memory[i];
		}
		i++;
	}
}
