/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/26 16:36:48 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	aux_help(void)
{
	ft_printf("./corewar [-dump bug] [-n] file [-n] file\n");
}

void		aux_print_champ(t_list *node)
{
	t_champion	*champion;

	champion = CHAMPION(node);
	ft_printf(
		"Pos: %d\nMagic: %d\nProg_name: %s\nProg_size: %d\nComment: %s\n\n",
		champion->nbr,
		champion->header.magic,
		champion->header.prog_name,
		champion->header.prog_size,
		champion->header.comment);
}

void		aux_ncurses(void)
{
	WINDOW *haut, *bas;

	initscr();
	haut= subwin(stdscr, LINES / 2, COLS, 0, 0);
    bas= subwin(stdscr, LINES / 2, COLS, LINES / 2, 0);
	mvwprintw(haut, 1, 1, "Ceci est la fenetre du haut");
    mvwprintw(bas, 1, 1, "Ceci est la fenetre du bas");
	box(haut, ACS_VLINE, ACS_HLINE);
    box(bas, ACS_VLINE, ACS_HLINE);
	//attron(A_STANDOUT);
	//printw("Hello World");
	//attroff(A_STANDOUT);
	//move(LINES / 2 - 1, COLS / 2 - 1);
	//addch('.');
	wrefresh(haut);
	wrefresh(bas);
	getch();
	endwin();
	free(haut);
	free(bas);
}

int			main(int argc, char **argv)
{
	t_pvm	vm;

	if (argc > 1)
	{
		aux_ncurses();
		init_vm(&vm);
		if (parse_arg(&vm, argc, argv))
		{
			init_memory(&vm);
			ft_lstiter(vm.champions, &aux_print_champ);
			print_memory(&vm);
			//start_vm(&vm);
		}
		free_vm(&vm);
	}
	else
		aux_help();
	return (0);
}
