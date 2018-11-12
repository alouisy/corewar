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

int	ft_lld(t_pvm *vm, t_process *process)
{
	int		value;
	int		address;

	value = 0;
	address = 0;
	if (vm->param[1] >= 1 && vm->param[1] <= REG_NUMBER
		&& get_prm_value(vm, process, 0, &value))
	{
		address = (process->pc + value) % MEM_SIZE;
		if (address < 0)
			address += MEM_SIZE;
		process->r[vm->param[1] - 1] = ft_strhex2dec(vm->memory, address, 4);
		if (vm->verbose == 2)
		{
			ft_printf("P% 5d | lld %d r%d\n",
					(CHAMPION(process->champ))->nbr,
					value,
					vm->param[1]);
		}
		ft_carry(process, process->r[vm->param[2] - 1], !(process->r[vm->param[2] - 1]));
	}
	return (1);
}

