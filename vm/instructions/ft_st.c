/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:01:23 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/23 17:51:17 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct store
*/

static void	write_in_memory(t_pvm *pvm, int address, int value)
{
	if (address < 0)
		address += MEM_SIZE;
	pvm->memory[(address + 3) % MEM_SIZE] = (value >> 0);
	pvm->memory[(address + 2) % MEM_SIZE] = (value >> 8);
	pvm->memory[(address + 1) % MEM_SIZE] = (value >> 16);
	pvm->memory[(address + 0) % MEM_SIZE] = (value >> 24);
}

void	ft_st(t_pvm *pvm, t_process *process)
{
	int		value;
	int		check;

	value = 0;
	check = 0;
	if (get_prm_value(pvm, process, 0, &value))
	{
		if (process->param_type[1] == REG_CODE)
		{
			if (process->param[1] >= 1 && process->param[1] <= REG_NUMBER)
			{
				check = 1;
				process->r[process->param[1] - 1] = value;
			}
		}
		else
		{
			check = 1;
			write_in_memory(pvm, (process->pc + (process->param[1] % IDX_MOD)), value);
		}
		if (check == 1 && value == 0)
			process->carry = 1;
		else if (check == 1 && value != 0)
			process->carry = 0;
	}
}
