/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:17:08 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/23 17:38:13 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** jump if zero
*/

void	ft_zjmp(UNUSED t_pvm *pvm, t_process *process)
{
	int		value;

	value = (short int)process->param[0];
	if (process->carry == 1)
	{
		if (!(pvm->nc.ncurses) && pvm->verbose)
		{
			ft_printf("P% 5d | zjmp %d OK\n", (CHAMPION(process->champ))->nbr, value);
		}
		process->pc += value % IDX_MOD;
		process->pc %= MEM_SIZE;
		while (process->pc < 0)
			process->pc += MEM_SIZE;
		process->pc2 = process->pc;
	}
	else
	{
		if (!(pvm->nc.ncurses) && pvm->verbose)
		{
			ft_printf("P% 5d | zjmp %d FAILED\n", (CHAMPION(process->champ))->nbr, value);
		}
	}
}
