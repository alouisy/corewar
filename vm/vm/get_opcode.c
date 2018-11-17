/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/17 22:06:00 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	get_opcode(t_pvm *vm, t_process *process)
{
	reset_param(vm);
	process->opcode = vm->memory[process->pc];
	if (process->opcode < 1 || process->opcode > 16)
	{
		process->opcode = 0;
		process->pc++;
		process->pc %= MEM_SIZE;
	}
	if (vm->verbose == 1)
	{
	
		get_param(vm, process, get_param_type(vm, process) + 1);
		store_buffer(
				vm, process->pc,
				vm->champions[(int)process->champ_nbr].color + 4,
				g_op_tab[process->opcode].nb_cycles + 1);
	}
	process->cycle_of_exe = vm->total_cycles + g_op_tab[process->opcode].nb_cycles - 1;
	return (vm->total_cycles + g_op_tab[process->opcode].nb_cycles - 2);
}
