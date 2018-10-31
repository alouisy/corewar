/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/27 19:35:10 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int			get_opcode(t_pvm *vm, t_process *process)
{
	int i;

	i = -1;
	if (g_op_tab[process->opcode].ocp)
	{
		process->ocp = vm->memory[process->pc + 1];
		while (++i < g_op_tab[process->opcode].nb_param)
		{
			process->param_type[i] = (vm->memory[process->pc + 1] & (0b11000000 >> (i * 2))) >> (6 - i * 2);
		}
		return (1);
	}
	else
		process->param_type[0] = DIR_CODE;
	return (0);
}

int			get_param(t_pvm *vm, t_process *process, int shift)
{
	int		i;
	int		label_size;

	i = 0;
	while (i < 3 && process->param_type[i])
	{
		label_size = process->param_type[i];
		if (label_size == DIR_CODE)
		{
			label_size += (g_op_tab[process->opcode].label_size == 1 ? 0 : 2);
		}
		process->param[i] = ft_strhex2dec(vm->memory + process->pc + shift, label_size);
		shift += label_size;
		i++;
	}
	return (shift);
}

void		get_instruction(t_pvm *vm, t_process *process)
{
	int		shift;

	shift = 1;
 	process->opcode = vm->memory[process->pc];
	if (process->opcode < 1 || process->opcode > 16)
	{
		process->opcode = 0;
		process->pc += 1;
	}
	else
	{
		shift += get_opcode(vm, process);
		shift = get_param(vm, process, shift);
		process->pc2 = process->pc + shift;
		process->cycle_bf_exe = g_op_tab[process->opcode].nb_cycles - 1;
	}
}
