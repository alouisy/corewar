/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:33 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 15:14:32 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** fork
*/

int		ft_fork(t_pvm *vm, t_process *process)
{
	int value;

	value = reverse_bytes(vm, PC + 1, 2);
	if (!aux_fork(vm, process, value % IDX_MOD))
		return (0);
	if ((vm->verbose - 1))
	{
		ft_printf("P% 5d | fork %d (%d)\n",
				-vm->champions[(int)process->champ_nbr].nbr,
				value,
				(PC + (value % IDX_MOD)));
		if (vm->verbose == 3)
			print_adv(vm, PC, 3);
	}
	PC = (PC + 3) % MEM_SIZE;
	return (1);
}
