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
	t_list		*node;
	t_champion	*champion;
	int			i;
	int			j;

	node = vm->champions;
	while (node)
	{
		i = 2;
		champion = CHAMPION(node);
		j = ((((champion->color - 1) * COLS) + 1) / vm->nb_champ);
		attron(COLOR_PAIR(champion->color));
		mvprintw(i++, j, "Prog_name: %s", champion->header.prog_name);
		attroff(COLOR_PAIR(champion->color));
		mvprintw(i++, j, "Pos: %d", champion->nbr);
		mvprintw(i++, j, "Prog_size: %d", champion->header.prog_size);
		mvprintw(i++, j, "Comment: %s", champion->header.comment);
		node = node->next;
	}
	refresh();
	getch();
}
