/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:47:27 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:20:49 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect load
*/

int	ft_ldi(t_pvm *vm, t_process *process)
{
	int		val1;
	int		val2;
	int		address;

	val1 = 0;
	val2 = 0;
	address = 0;
	if (vm->param[2] >= 1 && vm->param[2] <= REG_NUMBER
		&& get_prm_value(vm, process, 0, &val1)
		&& get_prm_value(vm, process, 1, &val2))
	{
/*		if (vm->param_type[1] == DIR_CODE)
			val1 = (short int)val1;
		val2 = (short int)vm->param[1];
*/		address = process->pc + ((val1 + val2) % IDX_MOD);
		if (vm->verbose == 2)
		{
			ft_printf("P% 5d | ldi %d %d r%d\n",
					(CHAMPION(process->champ))->nbr,
					val1,
					val2,
					vm->param[2]);
			ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
					val2,
					(val1 + val2), address);
		}
		if (address < 0)
			address += MEM_SIZE;
		process->r[vm->param[2] - 1] = ft_strhex2dec((vm->memory + (address % MEM_SIZE)), 4);
		ft_carry(process, process->r[vm->param[2] - 1],
				!(process->r[vm->param[2] - 1]));
	}
	return (1);
}
