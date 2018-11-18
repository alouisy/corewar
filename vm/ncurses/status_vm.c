/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/18 13:45:33 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** print information about vm in right panel
*/

int		status_vm(t_pvm *vm)
{
	int	i;

	i = 1;
	mvwprintw(vm->nc.wright, i++, 2, "step:	%d cycles / s", vm->nc.step);
	i++;
	mvwprintw(vm->nc.wright, i++, 2, "champions:	%8d", vm->nb_champ);
	mvwprintw(vm->nc.wright, i++, 2, "processes:	%8d", vm->nb_process);
	mvwprintw(vm->nc.wright, i++, 2, "cycle to die:	%8d", vm->c2d);
	mvwprintw(vm->nc.wright, i++, 2, "cycle delta:	%8d", CYCLE_DELTA);
	mvwprintw(vm->nc.wright, i++, 2, "current cycle:%8d",
			vm->c2d - ((vm->cycle_to_die - vm->total_cycles)));
	mvwprintw(vm->nc.wright, i++, 2, "total cycles: %8d", vm->total_cycles);
	mvwprintw(vm->nc.wright, i++, 2, "last live:	%8d", -vm->last_live);
	mvwprintw(vm->nc.wright, i++, 2, "number of lives:%6d", vm->sum_lives);
	mvwprintw(vm->nc.wright, i++, 2, "number of checks:%5d", vm->nb_checks);
	return (i);
}
