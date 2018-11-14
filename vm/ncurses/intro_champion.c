/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstprint_champion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:28:10 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** present each champions in first screen
*/

inline void intro_champions(t_pvm *vm)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	printf("k = %d\n", vm->nb_champ);
	while (k < vm->nb_champ)
	{
		i = 2;
		j = (((vm->champions[k].color - 1) * COLS) + 1) / vm->nb_champ;
		attron(COLOR_PAIR(vm->champions[k].color));
		mvprintw(i++, j, "Prog_name: %s", vm->champions[k].header.prog_name);
		attroff(COLOR_PAIR(vm->champions[k].color));
		mvprintw(i++, j, "Pos: %d", vm->champions[k].nbr);
		mvprintw(i++, j, "Prog_size: %d", vm->champions[k].header.prog_size);
		mvprintw(i++, j, "Comment: %s", vm->champions[k].header.comment);
		k++;
	}
	refresh();
	getch();
}
