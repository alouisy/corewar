/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:03:36 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 15:29:07 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** manage right panel during the game
*/

void		manage_step(t_pvm *vm, char c)
{
	if (c == 'w')
		vm->nc.step += 1;
	if (c == 'z')
		vm->nc.step -= 1;
	if (c == '+')
		vm->nc.step += 10;
	if (c == '-')
		vm->nc.step -= 10;
	if (vm->nc.step < 1)
		vm->nc.step = 1;
	else if (vm->nc.step > 1000)
		vm->nc.step = 1000;
	if (c == ' ')
		timeout(-1);
	else
		timeout(1000 / vm->nc.step);
}

void		status_game(t_pvm *vm)
{
	int		i;
	char	c;

	c = 0;
	i = status_vm(vm);
	i = status_champion(vm, i + 1);
	update_buffer(vm);
	status_process(vm, i + 2);
	wrefresh(vm->nc.wleft);
	wrefresh(vm->nc.wright);
	if ((c = getch()))
	{
		manage_step(vm, c);
	}
}
