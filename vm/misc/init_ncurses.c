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

static void	print_champion(t_list *node, WINDOW *win)
{
	t_champion	*champion;
	
	champion = CHAMPION(node);
	mvwprintw(win, 1, 1,
		"Pos: %d\n Magic: %d\n Prog_name: %s\n Prog_size: %d\n Comment: %s\n",
		champion->nbr,
		champion->header.magic,
		champion->header.prog_name,
		champion->header.prog_size,
		champion->header.comment);
}

void		init_ncurses(t_pvm *vm)
{
	t_list *tmp;

	initscr();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	vm->wleft = subwin(stdscr, LINES,  5 * COLS / 8, 0, 0);
	vm->wright = subwin(stdscr, LINES,  3 * COLS / 8, 0, 5 * COLS / 8);
	tmp = vm->champions;
	while (tmp)
	{
		print_champion(tmp, vm->wleft);
		tmp = tmp->next;
	}
	wattron(vm->wleft, A_BOLD);
	mvwprintw(vm->wleft, 6, 1, "Press any key:\n");
	wattroff(vm->wleft, A_BOLD);
	mvwprintw(vm->wright, 1, 1, "Process summary");
	box(vm->wleft, ACS_VLINE, ACS_HLINE);
	box(vm->wright, ACS_VLINE, ACS_HLINE);
	wrefresh(vm->wleft);
	wrefresh(vm->wright);
	getch();
}
