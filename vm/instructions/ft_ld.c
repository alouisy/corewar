/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:20:11 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct load
*/

static void	aux_verbose(t_pvm *vm, t_process *process, int value)
{
	if ((vm->verbose - 1))
	{
		ft_printf("P% 5d | ld %d r%d\n",
				vm->champions[(int)process->champ_nbr].nbr,
				value,
				vm->param[1]);
		if (vm->verbose == 3)
			print_adv(vm, process->pc, octal_shift(process->ocp, 4, 2));
	}
}

int	ft_ld(__attribute__((unused)) t_pvm *vm, t_process *process)
{
	int		value;

	value = 0;
	if (vm->param_type[1] == 1 && (vm->param_type[0] == 2 || vm->param_type[0] == 3))
	{
		if (vm->param[1] >= 1 && vm->param[1] <= REG_NUMBER)
		{
			if (vm->param_type[0] == DIR_CODE)
				value = reverse_bytes(vm, process->pc + 2, 4);
			else
			{
				value = reverse_bytes(vm, process->pc + 2, 2);
				value %= IDX_MOD;
				value = reverse_bytes(vm, process->pc + value, 4);
			}
			process->r[vm->param[1]] = value;
			ft_carry(process, value, !value);
		}
	}
	aux_verbose(vm, process, value);
	process->pc = (process->pc + octal_shift(vm->ocp, 4, 2)) % MEM_SIZE;
	return (1);
}
