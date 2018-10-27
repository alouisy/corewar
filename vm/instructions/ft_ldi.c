/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:47:27 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/24 17:34:25 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect load
*/

void	ft_ldi(t_pvm *pvm, t_process *process)
{
	int		val1;
	int		val2;
	int		address;

	val1 = 0;
	val2 = 0;
	address = 0;
	if (process->param[2] >= 1 && process->param[2] <= REG_NUMBER && get_prm_value(pvm, process, 0, &val1) && get_prm_value(pvm, process, 1, &val2))
	{
		address = process->pc + ((val1 + val2) % IDX_MOD);
		process->r[process->param[2] - 1] = ft_strhex2dec((pvm->memory + address), 4);
/*		if (address < 0)
			address += MEM_SIZE;
		process->r[process->param[2] - 1] = pvm->memory[(address) % MEM_SIZE] << 24;
		process->r[process->param[2] - 1] += pvm->memory[(address + 1) % MEM_SIZE] << 16;
		process->r[process->param[2] - 1] += pvm->memory[(address + 2) % MEM_SIZE] << 8;
		process->r[process->param[2] - 1] += pvm->memory[(address + 3) % MEM_SIZE];
*/		if (process->r[process->param[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}
