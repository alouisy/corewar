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

static void	aux_verbose(t_pvm *vm, t_process *process, int val1, int val2, int address)
{
	if ((vm->verbose - 1))
	{
		ft_printf("P% 5d | ldi %d %d r%d\n",
				vm->champions[(int)process->champ_nbr].nbr,
				val1,
				val2,
				vm->param[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
				val2,
				(val1 + val2),
				address);
		if (vm->verbose == 3)
			print_adv(vm, process->pc, octal_shift(process->ocp, 2, 3));
	}
}

int	ft_ldi(t_pvm *vm, t_process *process)
{
	int		val1;
	int		val2;
	int		address;

	val1 = 0;
	val2 = 0;
	address = 0;
	if (check_param(process->opcode, vm->ocp, g_op_tab[process->opcode].nb_param))
	{
		if (vm->param[2] >= 1 && vm->param[2] <= REG_NUMBER
			&& get_prm_value(vm, process, 0, &val1)
			&& get_prm_value(vm, process, 1, &val2))
		{
			address = process->pc + ((val1 + val2) % IDX_MOD);
			process->r[vm->param[2]] = reverse_bytes(vm, address, 4);
			ft_carry(process, process->r[vm->param[2]],
					!(process->r[vm->param[2]]));
		}
	}
	aux_verbose(vm, process, val1, val2, address);
	process->pc = (process->pc + octal_shift(vm->ocp, 2, 3)) % MEM_SIZE;
	return (1);
}
