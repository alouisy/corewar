/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prm_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:17:17 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/15 13:30:01 by jgroc-de         ###   ########.fr       */
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
			*value = process->r[vm->param[i]];
		else
			return (0);
	}
	else if (vm->param_type[i] == DIR_CODE)
		*value = vm->param[i];
	else
	{
		if (process->opcode != 13)
		{
			address = process->pc + (vm->param[i] % IDX_MOD);
		}
		else
			address = process->pc + vm->param[i];
		*value = reverse_bytes(vm, address, 4);
	}
	return (1);
}
