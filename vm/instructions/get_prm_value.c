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

int		get_prm_value(t_pvm *pvm, t_process *process, int i, int *value)
{
	int		address;

	address = 0;
	if (process->param_type[i] == REG_CODE)
	{
		if (process->param[i] >= 1 && process->param[i] <= REG_NUMBER)
			*value = process->r[process->param[i] - 1];
		else
			return (0);
	}
	else if (process->param_type[i] == DIR_CODE)
		*value = process->param[i];
	else 
	{
		if (process->opcode != 13)
		{
			address = process->pc + (process->param[i] % IDX_MOD);
			if (process->param[i] == 0xFFFF)
				address %= IDX_MOD;
		}
		else
			address = process->pc + process->param[i];
		address %= MEM_SIZE;
		if (address < 0)
			address += MEM_SIZE;
		*value = ft_strhex2dec((pvm->memory + (address % MEM_SIZE)), 4);
	}
	return (1);
}
