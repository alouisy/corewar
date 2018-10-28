/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:54:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 15:45:58 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect store
*/

void	ft_sti(t_pvm *pvm, t_process *process)
{
	int		val1;
	int		val2;
	int		val3;
	int		address;

	val1 = 0;
	val2 = 0;
	val3 = 0;
	address = 0;
	if (process->param[0] >= 1 && process->param[0] <= REG_NUMBER
		&& get_prm_value(pvm, process, 1, &val1) && get_prm_value(pvm, process, 2, &val2))
	{
		address = process->pc + ((val1 + val2) % IDX_MOD);
		if (address < 0)
			address += MEM_SIZE;
		val3 = process->r[process->param[0] - 1];
		pvm->memory[(address + 3) % MEM_SIZE] = val3;
		pvm->memory[(address + 2) % MEM_SIZE] = (val3 >> 8);
		pvm->memory[(address + 1) % MEM_SIZE] = (val3 >> 16);
		pvm->memory[(address + 0) % MEM_SIZE] = (val3 >> 24);
		if (process->r[process->param[0] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
}
