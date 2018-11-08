/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 15:30:35 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	aux_reset_memory(t_pvm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		vm->nc.memory[i] = vm->memory[i];
		print_case(vm->nc.wleft, i, vm->mem_color[i], vm->memory[i]);
		i++;
	}
}

void	aux_reset_stack(t_list stack[1001])
{
	int i;

	i = 0;
	while (i < 1001)
	{
		stack[i].content = NULL;
		stack[i].next = NULL;
		i++;
	}
}

void	init_ncurses(t_pvm *vm)
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	init_colors();
	intro_champions(vm);
	clear();
	vm->nc.left_width = 15 * COLS / 20;
	vm->nc.right_width = 5 * COLS / 20;
	vm->nc.wleft = subwin(stdscr, LINES, vm->nc.left_width, 0, 0);
	vm->nc.wright = subwin(stdscr, LINES, vm->nc.right_width, 0, vm->nc.left_width);
	vm->nc.step = 1;
	vm->nc.trash = NULL;
	aux_reset_memory(vm);
	aux_reset_stack(vm->nc.stack);
	box(vm->nc.wleft, ACS_VLINE, ACS_HLINE);
	box(vm->nc.wright, ACS_VLINE, ACS_HLINE);
	print_map(vm);
	status_game(vm);
	timeout(1000 / vm->nc.step);
	wrefresh(vm->nc.wleft);
}
