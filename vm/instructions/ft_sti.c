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

static void	aux_verbose(t_pvm *vm, t_process *process, int val1, int val2)
{
	if ((vm->verbose - 1))
	{
		ft_printf("P% 5d | sti r%d %d %d\n",
				vm->champions[(int)process->champ_nbr].nbr,
				vm->param[0],
				val1,
				val2);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
				val1,
				val2,
				(val1 + val2),
				PC + ((val1 + val2) % IDX_MOD));
		if (vm->verbose == 3)
			print_adv(vm, PC, octal_shift(OCP, 2, 3));
	}
}

int	ft_sti(t_pvm *vm, t_process *process)
{
	int		val1;
	int		val2;

	val1 = 0;
	val2 = 0;
	if (check_param(process->opcode, OCP, OP_TAB.nb_param))
	{
		if (vm->param_type[0] == 1 && vm->param[0] >= 1 && vm->param[0] <= REG_NUMBER
			&& get_prm_value(vm, process, 1, &val1)
			&& get_prm_value(vm, process, 2, &val2))
		{
			write_in_memory(vm, process, REG(vm->param[0]), val1 + val2);
			ft_carry(process, REG(vm->param[0]), !(REG(vm->param[0])));
		}
	}
	aux_verbose(vm, process, val1, val2);
	PC = (PC + octal_shift(OCP, 2, 3)) % MEM_SIZE;
	return (1);
}
