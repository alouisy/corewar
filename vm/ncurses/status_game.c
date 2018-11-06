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

int	update_pc(t_pvm *vm)
{
	int			color;
	t_list 		*node;
	t_process 	*process;

	node = vm->processes;
	while (node)
	{
		process = PROCESS(node);
		color = (CHAMPION(process->champ))->color + 4;
		print_case(vm->nc.wleft, process->pc, color, vm->memory[process->pc]);
		node = node->next;
	}
	return (1);
}

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
	if (vm->nc.clear)
	{
		wclear(vm->nc.wright);
		vm->nc.clear = 0;
		box(vm->nc.wright, ACS_VLINE, ACS_HLINE);
	}
	i = status_vm(vm);
	i = status_champion(vm, i + 1);
	status_process(vm, i + 2);
	print_map(vm);
	update_buffer(vm);
	update_pc(vm);
	wrefresh(vm->nc.wleft);
	wrefresh(vm->nc.wright);
	if ((c = getch()))
	{
		manage_step(vm, c);
	}
}
