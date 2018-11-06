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
/*
void	ft_del1(void *content, size_t size)
{
	(void)(content);
	(void)size;
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
		i = buffer->i;
		if (buffer->cycle)
			buffer->cycle--;
		if (buffer->cycle == 10)
		{
			wattron(vm->nc.wleft, COLOR_PAIR(buffer->color + 8));
			print_4case(vm->nc.wleft, i, (unsigned char*)buffer->str);
			wattroff(vm->nc.wleft, COLOR_PAIR(buffer->color + 8));
		}
		else if (!(buffer->cycle))
		{
			if (vm->memory[i] == 0)
				print_case(vm->nc.wleft, i, vm->memory[i]);
			else
			{
				wattron(vm->nc.wleft, COLOR_PAIR(buffer->color));
				print_4case(vm->nc.wleft, i, vm->memory + i);
				wattroff(vm->nc.wleft, COLOR_PAIR(buffer->color));
			}
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
*/
int	store_buffer(t_pvm *vm, int i, int color, int cycles)
{
	t_list 		*node;
	t_buffer	mem;

	mem.position = i;
	mem.color = color;
	mem.cycles_bf_end = cycles;
	if (!(node = ft_lstnew(&mem, sizeof(mem))))
		return (0);
	ft_lstadd(&(vm->nc.buffer), node);
	return (1);
}
