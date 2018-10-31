/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/24 17:37:01 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long direct load
*/

void	ft_lld(UNUSED t_pvm *pvm, t_process *process)
{
	int		value;
	int		address;

	value = 0;
	address = 0;
	if (process->param[1] >= 1 && process->param[1] <= REG_NUMBER
		&& get_prm_value(pvm, process, 0, &value))
	{
		address = (process->pc + value) % MEM_SIZE;
		while (address < 0)
			address += MEM_SIZE;
		process->r[process->param[1] - 1] = ft_strhex2dec((pvm->memory + (address % MEM_SIZE)), 4);
		if (process->r[process->param[1] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

