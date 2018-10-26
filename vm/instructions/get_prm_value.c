/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prm_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:43:40 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 16:06:02 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int		get_prm_value(t_pvm *pvm, t_process *process, int i)
{
	int		value;
	int		address;

	value = 0;
	if (process->param_type[i] == REG_CODE)
	{
		if (process->param[i] >= 1 && process->param[i] <= REG_NUMBER)
			value = process->r[process->param[i] - 1];
	}
	else if (process->param_type[i] == DIR_CODE)
		value = process->param[i];
	else
	{
		address = process->pc + (process->param[i] % IDX_MOD);
		if (address < 0)
			address += MEM_SIZE;
		value = pvm->memory[(address) % MEM_SIZE] << 24;
		value += pvm->memory[(address + 1) % MEM_SIZE] << 16;
		value += pvm->memory[(address + 2) % MEM_SIZE] << 8;
		value += pvm->memory[(address + 3) % MEM_SIZE];
	}
	return (value);
}
