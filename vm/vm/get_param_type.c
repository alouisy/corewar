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

int			get_param_type(t_pvm *vm, t_process *process)
{
	int i;
	int j;

	i = -1;
	if (g_op_tab[process->opcode].ocp)
	{
		while (++i < g_op_tab[process->opcode].nb_param)
		{
			vm->param_type[i] = (vm->memory[process->pc + 1] & (0b11000000 >> (i * 2))) >> (6 - i * 2);
			if (vm->param_type[i] == 3)
				vm->param_type[i] = 4;
			j = 1;
			while ((g_op_tab[process->opcode].param[i] & vm->param_type[i]) == 0)
			{
				vm->param_type[i] = j++;
			}
			if (vm->param_type[i] == 4)
				vm->param_type[i] = 3;
		}
		return (1);
	}
	else
		vm->param_type[0] = DIR_CODE;
	return (0);
}
