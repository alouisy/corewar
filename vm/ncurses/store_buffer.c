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

int	store_buffer(t_pvm *vm, int i, int color, int cycles)
{
	t_list 			*node;
	unsigned char	mem;

	if (vm->verbose == 1)
	{
		mem = color;
		if (vm->nc.trash)
		{
			node = vm->nc.trash;
			vm->nc.trash = node->next;
			*(unsigned char*)(node->content) = mem;
		}
		else if (!(node = ft_lstnew2(&mem, sizeof(mem))))
			return (0);
		node->content_size = i;
		node->next = (vm->nc.stack[(vm->total_cycles + cycles) % 1001]).next;
		(vm->nc.stack[(vm->total_cycles + cycles) % 1001]).next = node;
		if (cycles == 50)
			print_4case(vm, i, color);
		else
			print_case(vm->nc.wleft, i, color, vm->memory[i]);
	}
	return (1);
}
