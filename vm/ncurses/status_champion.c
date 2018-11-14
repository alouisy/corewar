/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_champion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:02:29 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:25:44 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** print information about champions in right panel
*/

int	status_champion(t_pvm *vm, int i)
{
	int			j;

	j = 0;
	while (j < vm->nb_champ)
	{
		wattron(vm->nc.wright, COLOR_PAIR(vm->champions[j].color));
		mvwprintw(vm->nc.wright, i++, 2, "name:	%s",
				vm->champions[j].header.prog_name);
		wattroff(vm->nc.wright, COLOR_PAIR(vm->champions[j].color));
		mvwprintw(vm->nc.wright, i++, 2, "	number: %d", vm->champions[j].nbr);
		mvwprintw(vm->nc.wright, i++, 2,
				"	last live: %d", vm->champions[j].l_live);
		mvwprintw(vm->nc.wright, i++, 2,
				"	nb of live: %-10d", vm->champions[j].nb_live);
		i++;
		j++;
	}
	return (i);
}
