/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:17:08 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 15:15:51 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** jump if zero
*/

int	ft_zjmp(t_pvm *vm, t_process *process)
{
	int		value;

	value = reverse_bytes(vm, PC + 1, 2);
	if ((process->state / 2))
	{
		PC = PC + (value % IDX_MOD);
		while (PC < 0)
			PC += MEM_SIZE;
		PC %= MEM_SIZE;
		if ((vm->verbose - 1))
			ft_printf("P% 5d | zjmp %d OK\n",
					-vm->champions[(int)process->champ_nbr].nbr, value);
	}
	else
	{
		if ((vm->verbose - 1))
		{
			ft_printf("P% 5d | zjmp %d FAILED\n",
					-vm->champions[(int)process->champ_nbr].nbr, value);
			if (vm->verbose == 3)
				print_adv(vm, PC, 3);
		}
		PC = (PC + 3) % MEM_SIZE;
	}
	return (1);
}
