/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:54:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:17:39 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect store
*/

int	ft_sti(t_pvm *vm, t_process *process)
{
	int		val1;
	int		val2;
	int		val3;
	int		address;

	val1 = 0;
	val2 = 0;
	val3 = 0;
	address = 0;
	if (vm->param[0] >= 1 && vm->param[0] <= REG_NUMBER
		&& get_prm_value(vm, process, 1, &val1) && get_prm_value(vm, process, 2, &val2))
	{
/*		if (vm->param_type[1] == DIR_CODE)
			val1 = (short int)val1;
		val2 = (short int)vm->param[2];
*/		address = process->pc + ((val1 + val2) % IDX_MOD);
		if (vm->verbose == 2)
		{
			ft_printf("P% 5d | sti r%d %d %d\n", (CHAMPION(process->champ))->nbr, vm->param[0], val1, val2);
			ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", val1, val2, (val1 + val2), address);
		}
		val3 = process->r[vm->param[0] - 1];
		write_in_memory(vm, process, val3, val1 + val2);
		ft_carry(process, val3, !val3);
	}
	return (1);
}
