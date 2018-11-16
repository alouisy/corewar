/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 18:13:51 by jgroc-de         ###   ########.fr       */
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

int	aux_andorxor(t_pvm *vm, t_list *node, int mode,
		void (*f)(t_pvm *, t_list *, int, int))
{
	int			val1;
	int			val2;
	t_process	*process;

	process = get_process(node);
	val1 = 0;
	val2 = 0;
	if (check_param(process->opcode, OCP, OP_TAB.nb_param))
	{
		if (vm->param[2] >= 1 && vm->param[2] <= REG_NUMBER
			&& get_prm_value(vm, process, 0, &val1)
			&& get_prm_value(vm, process, 1, &val2))
		{
			if (mode == 1)
				REG(vm->param[2]) = (val1 & val2);
			else if (mode == 2)
				REG(vm->param[2]) = (val1 | val2);
			else if (mode == 3)
				REG(vm->param[2]) = (val1 ^ val2);
			ft_carry(process, REG(vm->param[2]), !(REG(vm->param[2])));
		}
	}
	f(vm, node, val1, val2);
	PC = (PC + octal_shift(OCP, 4, 3)) % MEM_SIZE;
	return (1);
}
