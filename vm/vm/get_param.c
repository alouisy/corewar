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

int	get_param(t_pvm *vm, t_process *process, int shift)
{
	int		i;
	int		label_size;

	i = -1;
	while (++i < g_op_tab[process->opcode].nb_param)
	{
		label_size = vm->param_type[i];
		if (label_size == DIR_CODE)
			label_size += (g_op_tab[process->opcode].label_size == 1 ? 0 : 2);
		else if (label_size == IND_CODE)
			label_size -= 1;
		vm->param[i] = ft_strhex2dec(vm->memory + ((process->pc + shift) % MEM_SIZE), label_size);
		if (label_size != 1)// && vm->param_type[i] == IND_CODE)
			vm->param[i] = (short int)vm->param[i];
		shift += label_size;
	}
	return (shift);
}
