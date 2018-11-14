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

int	ft_zjmp(t_pvm *vm, t_process *process)
{
	int		value;

	value = reverse_bytes(vm, process->pc + 1, 2);
	if (process->state / 2)
	{
		process->pc = (unsigned int)(process->pc + (value % IDX_MOD)) % MEM_SIZE;
		if ((vm->verbose - 1))
			ft_printf("P% 5d | zjmp %d OK\n", (CHAMPION(process->champ))->nbr, value);
	}
	else
	{
		if ((vm->verbose - 1))
		{
			ft_printf("P% 5d | zjmp %d FAILED\n", (CHAMPION(process->champ))->nbr, value);
			if (vm->verbose == 3)
				print_adv(vm, process->pc, 3);
		}
		process->pc = (process->pc + 3) % MEM_SIZE;
	}
	return (1);
}
