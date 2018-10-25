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

void	ft_st(t_pvm *pvm, t_process *process)
{
	int		value;
	int		address;

	value = process->r[process->param[0] - 1];
	if (process->param_type[1] == REG_CODE)
		if (process->param[1] >= 1 && process->param[1] <= REG_NUMBER)
			process->r[process->param[1] - 1] = value;
	else
	{
		address = process->pc + (process->param[1] % IDX_MOD);
		while (address < 0)
			address += MEM_SIZE;
		pvm->memory[(address + 3) % MEM_SIZE] = value;
		pvm->memory[(address + 2) % MEM_SIZE] = (value >> 8);
		pvm->memory[(address + 1) % MEM_SIZE] = (value >> 16);
		pvm->memory[(address + 0) % MEM_SIZE] = (value >> 24);
	}
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
