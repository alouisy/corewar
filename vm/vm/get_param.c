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

int		reverse_bytes(t_pvm *vm, int pc, int nbytes)
{
	char			one_byte;
	unsigned char	two_bytes[2];
	unsigned char	four_bytes[4];

	while (pc < 0)
		pc += MEM_SIZE;
	if (nbytes == 1)
	{
		one_byte = vm->memory[(unsigned int)(pc) % MEM_SIZE];
		return (one_byte);
	}
	if (nbytes == 2)
	{
		two_bytes[0] = vm->memory[(unsigned int)(pc + 1) % MEM_SIZE];
		two_bytes[1] = vm->memory[(unsigned int)(pc) % MEM_SIZE];
		return (*(short *)&two_bytes[0]);
	}
	if (nbytes == 4)
	{
		four_bytes[0] = vm->memory[(unsigned int)(pc + 3) % MEM_SIZE];
		four_bytes[1] = vm->memory[(unsigned int)(pc + 2) % MEM_SIZE];
		four_bytes[2] = vm->memory[(unsigned int)(pc + 1) % MEM_SIZE];
		four_bytes[3] = vm->memory[(unsigned int)(pc) % MEM_SIZE];
		return (*(int *)&four_bytes[0]);
	}
	return (-1);
}

int	get_param(t_pvm *vm, t_process *process, int shift)
{
	int		i;
	int		label_size;

	i = -1;
	while (++i < OP_TAB.nb_param)
	{
		label_size = vm->param_type[i];
		if (label_size == DIR_CODE)
			label_size += (OP_TAB.label_size == 1 ? 0 : 2);
		else if (label_size == IND_CODE)
			label_size -= 1;
		vm->param[i] = reverse_bytes(vm, (PC + shift), label_size);
		shift += label_size;
	}
	return (shift);
}
