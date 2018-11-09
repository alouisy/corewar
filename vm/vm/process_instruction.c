/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/09 15:08:45 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	process_instruction(t_pvm *vm, t_process *process)
{
	if (!(vm->f[process->opcode - 1](vm, process)))
	{
		vm->c2d = -1;
		return (0);
	}
	reset_param(process);
	process->pc = process->pc2;
	process->opcode = 0;
	process->ocp = 0;
	process->cycle_of_exe = vm->total_cycles;
	return (1);
}
