/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/18 13:10:45 by jgroc-de         ###   ########.fr       */
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

int		aux_andorxor(t_pvm *vm, t_list *node, int mode,
		void (*f)(t_pvm *, t_list *, int, int))
{
	int			val[2];
	t_process	*process;
	int			*registre;

	process = get_process(node);
	registre = reg(process, vm->param[2]);
	val[0] = 0;
	val[1] = 0;
	if (check_param(process->opcode, vm->ocp, OP_TAB.nb_param)
			&& vm->param[2] >= 1 && vm->param[2] <= REG_NUMBER
			&& get_prm_value(vm, process, 0, &val[0])
			&& get_prm_value(vm, process, 1, &val[1]))
	{
		if (mode == 1)
			*registre = (val[0] & val[1]);
		else if (mode == 2)
			*registre = (val[0] | val[1]);
		else if (mode == 3)
			*registre = (val[0] ^ val[1]);
		ft_carry(process, *registre, !(*registre));
		f(vm, node, val[0], val[1]);
	}
	update_pc(vm, process, 4, 3);
	return (1);
}
