/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:02:29 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:25:44 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	champion_status(t_pvm *vm, int i)
{
	t_list		*node;
	t_champion	*champion;

	node = vm->champions;
	while (node)
	{
		champion = CHAMPION(node);
		wattron(vm->nc.wright, COLOR_PAIR(champion->color));
		mvwprintw(vm->nc.wright, i++, 2, "name:	%s",
				champion->header.prog_name);
		wattroff(vm->nc.wright, COLOR_PAIR(champion->color));
		mvwprintw(vm->nc.wright, i++, 2, "	number: %d", champion->nbr);
		mvwprintw(vm->nc.wright, i++, 2,
				"	last live: %d", champion->l_live);
		mvwprintw(vm->nc.wright, i++, 2,
				"	nb of live: %-10d", champion->nb_live);
		i++;
		node = node->next;
	}
	return (i);
}
