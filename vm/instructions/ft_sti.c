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
	int		value;
	int		address;

	value = process->r[process->param[0] - 1];
	address = process->pc
		+ ((get_prm_value(pvm, process, 1, &value) + get_prm_value(pvm, process, 2, &value))
		% IDX_MOD);
	if (address < 0)
		address += MEM_SIZE;
	pvm->memory[(address + 3) % MEM_SIZE] = value;
	pvm->memory[(address + 2) % MEM_SIZE] = (value >> 8);
	pvm->memory[(address + 1) % MEM_SIZE] = (value >> 16);
	pvm->memory[(address + 0) % MEM_SIZE] = (value >> 24);
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
