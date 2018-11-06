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
** update process state champion's memory in left panel
*/

void	ft_del1(void *content)
{
	(void)(content);
}

void	update_buffer(t_pvm *vm)
{
	int			i;
	t_list		*node;
	t_list		*todel;
	t_buffer	*buffer;

	node = vm->nc.buffer;
	todel = NULL;
	while (node)
	{
		buffer = get_buffer(node);
		i = buffer->position;
		if (buffer->cycles_bf_end)
		{
			buffer->cycles_bf_end--;
			print_4case(vm, i, buffer->color);
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
			todel = NULL;
		}
	}
}

int	store_buffer(t_pvm *vm, int i, int color, int cycles)
{
	t_list 		*node;
	t_buffer	mem;

	mem.position = i;
	mem.color = color;
	mem.cycles_bf_end = cycles;
	if (!(node = ft_lstnew2(&mem, sizeof(mem))))
		return (0);
	ft_lstadd(&(vm->nc.buffer), node);
	return (1);
}
