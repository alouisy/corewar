/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prm_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:17:17 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:17:18 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int		get_prm_value(t_pvm *vm, t_process *process, int i, int *value)
{
	int		address;

	address = 0;
	if (vm->param_type[i] == REG_CODE)
	{
		if (vm->param[i] >= 1 && vm->param[i] <= REG_NUMBER)
			*value = process->r[vm->param[i] - 1];
		else
			return (0);
	}
	else if (vm->param_type[i] == DIR_CODE)
		*value = vm->param[i];
	else 
	{
		vm->param[i] %= MEM_SIZE;
		if (vm->param[i] > MEM_SIZE / 2)
			vm->param[i] -= MEM_SIZE;
		if (process->opcode != 13)
			address = process->pc + (vm->param[i] % IDX_MOD);
		else
			address = process->pc + vm->param[i];
		address %= MEM_SIZE;
		if (address < 0)
			address += MEM_SIZE;
		if (process->opcode != 13)
			*value = ft_strhex2dec(vm->memory, address, 4);
		else
		{
			*value = ft_strhex2dec(vm->memory, address, 2);
			if (*value > 32768)
				*value -= 65536;
		}
	}
	return (1);
}
