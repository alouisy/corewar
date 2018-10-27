/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 19:34:41 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	process_instruction(t_pvm *vm, t_process *process)
{
	//printf("It's now cycle %d\n", vm->total_cycles);
	//printf("%d cycles before exe of '%s' : \n", process->cycle_bf_exe - 1, g_op_tab[process->opcode].name);
	if (--process->cycle_bf_exe == 0)
	{
		vm->f[process->opcode - 1](vm, process);
		process->pc = process->pc2;
		process->opcode = -1;
		process->ocp = 0;
	}
}
