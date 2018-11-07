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
** store modification of vm->memory for highlighting in ncurses
*/

int	store_buffer(t_pvm *vm, int i, int color, int cycles)
{
	t_list 		*node;
	t_buffer	mem;

	if (vm->nc.ncurses)
	{
		mem.position = i;
		mem.color = color;
		if (!(node = ft_lstnew2(&mem, sizeof(mem))))
			return (0);
		node->next = (vm->nc.stack[(vm->cur_cycle + cycles) % 1001]).next;
		(vm->nc.stack[(vm->cur_cycle + cycles) % 1001]).next = node;
		if (cycles == 50)
			print_4case(vm, i, color);
		else
			print_case(vm->nc.wleft, i, color, vm->memory[i]);
	}
	return (1);
}
