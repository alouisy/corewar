/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:19:53 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** loqical and
*/

int	ft_and(__attribute__((unused)) t_pvm *vm, t_process *process)
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
			process->r[vm->param[2] - 1] = (val1 & val2);
			if (vm->verbose == 2)
			{
				ft_printf("P% 5d | and %d %d r%d\n",
						(CHAMPION(process->champ))->nbr,
						val1,
						val2,
						vm->param[2]);
			}
			ft_carry(process, process->r[vm->param[2] - 1], !(process->r[vm->param[2] - 1]));
		}
	}
	if (vm->verb == 3)
		print_adv(vm, process->pc, octal_shift(process->ocp, 4, 3));
	process->pc = (process->pc + octal_shift(process->ocp, 4, 3)) % MEM_SIZE;
	return (1);
}
/*
int	ft_and(__attribute__((unused)) t_pvm *vm, t_process *process)
{
	int		val1;
	int		val2;

	val1 = 0;
	val2 = 0;
	if (vm->param[2] >= 1 && vm->param[2] <= REG_NUMBER
		&& get_prm_value(vm, process, 0, &val1)
		&& get_prm_value(vm, process, 1, &val2))
	{
		process->r[vm->param[2] - 1] = (val1 & val2);
		if (vm->verbose == 2)
		{
			ft_printf("P% 5d | and %d %d r%d\n",
					(CHAMPION(process->champ))->nbr,
					val1,
					val2,
					vm->param[2]);
		}
		ft_carry(process, (val1 & val2), !(val1 & val2));
	}
	return (1);
}
*/