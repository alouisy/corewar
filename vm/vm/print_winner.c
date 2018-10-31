/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/29 19:01:00 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline void	print_winner(t_pvm *vm)
{
	t_list	*champ;

	champ = vm->champions;
	while (champ)
	{
		if ((CHAMPION(champ))->l_live >= vm->last_live)
			break ;
		champ = champ->next;
	}
	if (vm->nc.ncurses)
	{
		clear();
		mvprintw(LINES / 2, COLS / 2, "le joueur %s(%d) a gagne\n", (CHAMPION(champ))->header.prog_name, (CHAMPION(champ))->nbr);
		getch();
	}
	else
		ft_printf("le joueur %d(%s) a gagne\n", (CHAMPION(champ))->nbr, (CHAMPION(champ))->header.prog_name);
}
