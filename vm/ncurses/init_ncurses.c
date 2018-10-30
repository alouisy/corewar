/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/30 18:11:52 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void		init_ncurses(t_pvm *vm)
{
	initscr();
	keypad(stdscr, TRUE);
	set_color();
	lstprint_champion(vm);
	clear();
	print_map(vm);
	insert_champion(vm);
	game_status(vm);
	vm->nc.buffer = NULL;
	wrefresh(vm->nc.wleft);
}
