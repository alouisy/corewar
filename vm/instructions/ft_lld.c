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
	int		label_size;

	value = 0;
	address = 0;
	label_size = 4;
	if (process->param[1] >= 1 && process->param[1] <= REG_NUMBER
		&& get_prm_value(pvm, process, 0, &value))
	{
		if (process->param_type[0] == IND_CODE)
			label_size = 2;
		address = process->pc + value;
		while (address < 0)
			address += MEM_SIZE;
		process->r[process->param[1] - 1] = ft_strhex2dec((pvm->memory + (address % MEM_SIZE)), label_size);
		if (!(pvm->nc.ncurses) && pvm->verbose == 2)
		{
			ft_printf("P% 5d | lld %d r%d\n", process->champ_nbr, value, process->param[1]);
		}
		if (process->r[process->param[1] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}

