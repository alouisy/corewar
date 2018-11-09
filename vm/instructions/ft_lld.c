/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:21:27 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long direct load
*/

int	ft_lld(t_pvm *pvm, t_process *process)
{
	int		value;
	int		address;

	value = 0;
	address = 0;
	if (process->param[1] >= 1 && process->param[1] <= REG_NUMBER
		&& get_prm_value(pvm, process, 0, &value))
	{
/*		if (process->param_type[0] == IND_CODE)
			value = (short int)value;
*/		address = (process->pc + value) % MEM_SIZE;
		while (address < 0)
			address += MEM_SIZE;
		process->r[process->param[1] - 1] = ft_strhex2dec((pvm->memory + (address % MEM_SIZE)), 4);
		if (pvm->verbose == 2)
		{
			ft_printf("P% 5d | lld %d r%d\n",
					(CHAMPION(process->champ))->nbr,
					value,
					process->param[1]);
		}
		ft_carry(process, process->r[process->param[2] - 1], !(process->r[process->param[2] - 1]));
	}
	return (1);
}

