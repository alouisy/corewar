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

void	ft_del1(void *content)
{
	(void)(content);
}

void	update_buffer(t_pvm *vm)
{
	t_list		*node;
	t_list		*todel;
	t_buffer	*buffer;

	node = vm->nc.buffer;
	while (node)
	{
		todel = NULL;
		buffer = get_buffer(node);
		if (buffer->cycles_bf_end)
		{
			buffer->cycles_bf_end--;
			print_4case(vm, buffer->position, buffer->color);
		}
		else if (!(buffer->cycles_bf_end))
		{
			todel = ft_lstpop(node, &(vm->nc.buffer));
		}
		node = node->next;
		if (todel)
		{
			ft_lstdelone(&todel, &ft_del1);
			free(todel);
		}
	}
}
