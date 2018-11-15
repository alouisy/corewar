/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/15 12:30:13 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	get_opcode(t_pvm *vm, t_process *process)
{
	process->opcode = vm->memory[process->pc % MEM_SIZE];
	if (process->opcode < 1 || process->opcode > 16)
	{
		process->opcode = 0;
		process->pc++;
		process->pc %= MEM_SIZE;
	}
	if (vm->verbose == 1)
	{
		store_buffer(
				vm, process->pc,
				vm->champions[(int)process->champ_nbr].color + 4,
				g_op_tab[process->opcode].nb_cycles + 1);
	}
	return (vm->total_cycles + g_op_tab[process->opcode].nb_cycles - 2);
}
