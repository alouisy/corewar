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

void	reset_param(t_process *process)
{
	int i;

	i = 0;
	while (i < 3)
	{
		process->param_type[i] = 0;;
		process->param[i] = 0;;
		i++;
	}
}

void	process_instruction(t_pvm *vm, t_process *process)
{
	if (--process->cycle_bf_exe == 0)
	{
		vm->f[process->opcode - 1](vm, process);
		reset_param(process);
		process->pc = process->pc2;
		process->opcode = 0;
		process->ocp = 0;
	}
}
