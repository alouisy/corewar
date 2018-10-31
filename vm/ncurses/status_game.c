/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:03:36 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:03:37 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** manage right panel during the game
*/

void		status_game(t_pvm *vm)
{
	int i;

	wrefresh(vm->nc.wleft);
	if (!(vm->cur_cycle % 20))
	{
		wclear(vm->nc.wright);
		box(vm->nc.wright, ACS_VLINE, ACS_HLINE);
		i = status_vm(vm);
		i = status_champion(vm, i + 1);
		status_process(vm, i + 2);
		wrefresh(vm->nc.wright);
		getch();
	}
}
