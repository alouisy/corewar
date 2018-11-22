/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/18 16:00:03 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int	get_winner(t_pvm *vm)
{
	int i;

	i = 0;
	while (i < vm->nb_champ)
	{
		if (vm->champions[i].nbr == vm->last_live)
		{
			return (i);
		}
		i++;
	}
	return (vm->nb_champ - 1);
}

inline void	print_winner(t_pvm *vm)
{
	int	i;

	i = get_winner(vm);
	if (vm->nc_mode)
	{
		timeout(-1);
		status_game(vm);
		getch();
		clear();
		mvprintw(LINES / 2, COLS / 2 - 30,
				"Contestant %d, \"%s\", has won, GG!!\n",
				-vm->champions[i].nbr,
				vm->champions[i].header.prog_name);
		getch();
	}
	else if (vm->nb_process == 0)
	{
		ft_printf("Contestant %d, \"%s\", has won !\n",
				-vm->champions[i].nbr,
				vm->champions[i].header.prog_name);
	}
}
