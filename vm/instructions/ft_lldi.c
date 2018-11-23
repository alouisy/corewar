/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:23 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/23 20:15:48 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect load
*/

static void	aux_verbose(t_pvm *vm, t_list *node, int val1, int val2)
{
	t_process	*proc;

	proc = get_process(node);
	if (vm->verbose & 4)
	{
		ft_printf("P% 5d | lldi %d %d r%d\n",
				node->content_size,
				val1,
				val2,
				vm->param[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
				val1,
				val2,
				(val1 + val2),
				proc->pc + val1 + val2);
	}
}

int			ft_lldi(t_pvm *vm, t_list *node)
{
	int			val1;
	int			val2;
	t_process	*proc;
	int			*registre;

	proc = get_process(node);
	registre = reg(proc, vm->param[2]);
	val1 = 0;
	val2 = 0;
	if (check_param(proc->opcode, vm->ocp, g_op_tab[proc->opcode].nb_param)
			&& is_reg(vm, 2)
			&& get_prm_value(vm, proc, 0, &val1)
			&& get_prm_value(vm, proc, 1, &val2))
	{
		*registre = reverse_bytes(vm, proc->pc + val1 + val2, 4);
		ft_carry(proc, *registre);
		aux_verbose(vm, node, val1, val2);
	}
	update_pc(vm, proc, 2, 3);
	return (1);
}
