/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:23 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 15:47:12 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect load
*/

static void	aux_verbose(t_pvm *vm, t_process *process, int val1, int val2)
{
	if ((vm->verbose - 1))
	{
		ft_printf("P% 5d | lldi %d %d r%d\n",
				(CHAMPION(process->champ))->nbr,
				val1,
				val2,
				vm->param[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
				val1,
				val2,
				(val1 + val2),
				process->pc + val1 + val2);
		if (vm->verbose == 3)
			print_adv(vm, process->pc, octal_shift(process->ocp, 2, 3));
	}
}

int	ft_lldi(t_pvm *vm, t_process *process)
{
	int		val1;
	int		val2;

	val1 = 0;
	val2 = 0;
	if (check_param(process->opcode, process->ocp, g_op_tab[process->opcode].nb_param))
	{
		if (vm->param[2] >= 1 && vm->param[2] <= REG_NUMBER
			&& get_prm_value(vm, process, 0, &val1)
			&& get_prm_value(vm, process, 1, &val2))
		{
			process->r[vm->param[2]] = reverse_bytes(vm, process->pc + val1 + val2, 4);
			ft_carry(process, val1, !val1);
		}
	}
	aux_verbose(vm, process, val1, val2);
	process->pc = (process->pc + octal_shift(process->ocp, 2, 3)) % MEM_SIZE;
	return (1);
}
