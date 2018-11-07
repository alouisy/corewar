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
	t_buffer	*buffer;

	node = (vm->nc.stack[vm->cur_cycle % 1001]).next;
	while (node)
	{
		buffer = get_buffer(node);
		print_4case(vm, buffer->position, vm->mem_color[buffer->position]);
		free(node->content);
		free(node);
		node = node->next;
	}
	(vm->nc.stack[vm->cur_cycle % 1001]).next = NULL;
}
