/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/27 20:24:14 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int		vm_status(t_pvm *vm)
{
	int	i;

	i = 1;
	mvwprintw(vm->nc.wright, i++, 2, "champions: %d", vm->nb_champ);
	mvwprintw(vm->nc.wright, i++, 2, "processes: %d",
			ft_lstlength(vm->processes));
	mvwprintw(vm->nc.wright, i++, 2, "cycle to die: %d", vm->cycle_to_die);
	mvwprintw(vm->nc.wright, i++, 2, "current cycle: %d", vm->cur_cycle);
	mvwprintw(vm->nc.wright, i++, 2, "last live: %d", vm->last_live);
	mvwprintw(vm->nc.wright, i++, 2, "number of lives: %d", vm->sum_lives);
	mvwprintw(vm->nc.wright, i++, 2, "number of checks: %d", vm->nb_checks);
	return (i);
}
