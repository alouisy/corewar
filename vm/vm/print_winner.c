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
	int i;

	i = 0;
	while (i < vm->nb_champ)
	{
		if (vm->champions[i].l_live >= vm->last_live)
			break ;
		i++;
	}
	if (vm->verbose == 1)
	{
		clear();
		timeout(-1);
		mvprintw(LINES / 2, COLS / 2 - 30, "le joueur %d(%s) a gagne\n",
				-vm->champions[i].nbr,
				vm->champions[i].header.prog_name);
		getch();
	}
	else
	{
		ft_printf("Contestant %d, \"%s\", has won !\n",
				-vm->champions[i].nbr,
				vm->champions[i].header.prog_name);
	}
}
