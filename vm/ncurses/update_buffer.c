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
	t_list		*node;
	t_list		*save;
	t_buffer	*buffer;

	node = (vm->nc.stack[vm->total_cycles % 1001]).next;
	while (node)
	{
		buffer = get_buffer(node);
		save = node->next;
		print_4case(vm, buffer->position, vm->mem_color[buffer->position]);
		node->next = vm->nc.trash;
		vm->nc.trash = node;
		node = save;
	}
	(vm->nc.stack[vm->total_cycles % 1001]).next = NULL;
}
