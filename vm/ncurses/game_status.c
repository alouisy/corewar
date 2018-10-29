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

void		game_status(t_pvm *vm)
{
	int i;

	i = vm_status(vm);
	i = champion_status(vm, i + 1);
	process_status(vm, i + 2);
	if (!(vm->cur_cycle % 5))
	{
		wrefresh(vm->nc.wleft);
		wrefresh(vm->nc.wright);
		getch();
	}
}
