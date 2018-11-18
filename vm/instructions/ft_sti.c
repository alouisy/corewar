/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:54:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/17 15:31:22 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect store
*/

static void	aux_verbose(t_pvm *vm, t_list *node, int val1, int val2)
{
	if (vm->verbose == 3)
	{
		ft_printf("P% 5d | sti r%d %d %d\n",
				node->content_size,
				vm->param[0],
				val1,
				val2);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
				val1,
				val2,
				(val1 + val2),
				(get_process(node))->pc + ((val1 + val2) % IDX_MOD));
	}
}

int			ft_sti(t_pvm *vm, t_list *node)
{
	int			val1;
	int			val2;
	t_process	*proc;

	proc = get_process(node);
	val1 = 0;
	val2 = 0;
	if (check_param(proc->opcode, vm->ocp, g_op_tab[proc->opcode].nb_param)
			&& is_reg(vm, 0)
			&& get_prm_value(vm, proc, 1, &val1)
			&& get_prm_value(vm, proc, 2, &val2))
	{
		write_in_memory(vm, proc, *(reg(proc, vm->param[0])),
				val1 + val2);
		aux_verbose(vm, node, val1, val2);
	}
	update_pc(vm, proc, 2, 3);
	return (1);
}
