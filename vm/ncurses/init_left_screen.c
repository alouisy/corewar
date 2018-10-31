/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:26:36 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** insert each champion's programme in left panel
*/

static inline void	insert_champion(t_pvm *vm)
{
	unsigned int	i;
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
				wattron(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color + 4));
				print_case(vm->nc.wleft, i, i + pos, (CHAMPION(node))->prog);
				wattroff(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color + 4));
				wattron(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color));
			}
			else
				print_case(vm->nc.wleft, i, i + pos, (CHAMPION(node))->prog);
			i++;
		}
		wattroff(vm->nc.wleft, COLOR_PAIR((CHAMPION(node))->color));
		node = node->next;
	}
}

/*
** first print of map with "00" only
*/

static inline void	init_map(t_pvm *vm)
{
	unsigned int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		mvwprintw(vm->nc.wleft, i / 64 + 1, (i % 64) * 3 + 1, "00");
		if ((i % 64) == 0)
			mvwprintw(vm->nc.wleft, i / 64 + 2, (i % 64) * 3 + 1, " ");
		i++;
	}
}

void	init_left_panel(t_pvm *vm)
{
	init_map(vm);
	insert_champion(vm);
}
