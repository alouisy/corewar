/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/23 20:18:28 by jgroc-de         ###   ########.fr       */
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
	t_process	*proc;
	int			*registre;

	proc = get_process(node);
	registre = reg(proc, vm->param[2]);
	val[0] = 0;
	val[1] = 0;
	if (check_param(proc->opcode, vm->ocp, g_op_tab[proc->opcode].nb_param)
			&& vm->param[2] >= 1 && vm->param[2] <= REG_NUMBER
			&& get_prm_value(vm, proc, 0, &val[0])
			&& get_prm_value(vm, proc, 1, &val[1]))
	{
		if (mode == 1)
			*registre = (val[0] & val[1]);
		else if (mode == 2)
			*registre = (val[0] | val[1]);
		else if (mode == 3)
			*registre = (val[0] ^ val[1]);
		ft_carry(proc, *registre);
		f(vm, node, val[0], val[1]);
	}
	update_pc(vm, proc, 4, 3);
	return (1);
}
