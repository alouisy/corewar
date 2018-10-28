/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 20:23:42 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	insert_champion(t_pvm *vm)
{
	unsigned int 	i;
	int				pos;
	t_list			*node;

	i = 0;
	node = vm->champions;
	while (node)
	{
		i = 0;
		pos = (CHAMPION(node))->vm_pos;
		wattron(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color));
		while (i < (CHAMPION(node))->header.prog_size)
		{
			if (i == 0)
			{
				wattroff(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color));
				wattron(vm->nc.wleft, COLOR_PAIR(5));
				mvwprintw(vm->nc.wleft, (i + pos) / 64 + 1, ((i + pos) % 64) * 3 + 1, "%.2hhx", (CHAMPION(node))->prog[i]);
				wattroff(vm->nc.wleft, COLOR_PAIR(5));
				wattron(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color));
			}
			else
				mvwprintw(vm->nc.wleft, (i + pos) / 64 + 1, ((i + pos) % 64) * 3 + 1, "%.2hhx", (CHAMPION(node))->prog[i]);
			i++;
		}
		wattroff(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color));
		node = node->next;
	}
	wrefresh(vm->nc.wleft);
}
