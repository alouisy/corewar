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
** mode :
**		1 : and/&
**		2 : or/|
**		3 : xor/^
** f : verbose function
*/

int	aux_andorxor(t_pvm *vm, t_process *process, int mode, void (*f)(t_pvm *, t_process *, int ,int))
{
	int		val1;
	int		val2;

	val1 = 0;
	val2 = 0;
	if (check_param(process->opcode, process->ocp, g_op_tab[process->opcode].nb_param))
	{
		if (vm->param[2] >= 1 && vm->param[2] <= REG_NUMBER)
		{
			get_prm_value(vm, process, 0, &val1);
			get_prm_value(vm, process, 1, &val2);
			if (mode == 1)
				process->r[vm->param[2] - 1] = (val1 & val2);
			else if (mode == 2)
				process->r[vm->param[2] - 1] = (val1 | val2);
			else if (mode == 3)
				process->r[vm->param[2] - 1] = (val1 ^ val2);
			ft_carry(process, process->r[vm->param[2] - 1], !(process->r[vm->param[2] - 1]));
		}
	}
	f(vm, process, val1, val2);
	process->pc = (process->pc + octal_shift(process->ocp, 4, 3)) % MEM_SIZE;
	return (1);
}
