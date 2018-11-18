/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/17 15:31:32 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long direct load
*/

static void	aux_verbose(t_pvm *vm, t_list *node, int value)
{
	if (vm->verbose == 3)
	{
		ft_printf("P% 5d | lld %d r%d\n",
				node->content_size,
				value,
				vm->param[1]);
	}
}

int			ft_lld(t_pvm *vm, t_list *node)
{
	int			value;
	t_process	*proc;
	int			*registre;
	
	proc = get_process(node);
	registre = reg(proc, vm->param[1]);
	value = 0;
	if (check_param(proc->opcode, vm->ocp, g_op_tab[proc->opcode].nb_param)
			&& is_reg(vm, 1))
	{
		if (vm->param_type[0] == IND_CODE)
			value = reverse_bytes(vm, (proc->pc + vm->param[0]), 2);
		else if (vm->param_type[0] == DIR_CODE)
			value = reverse_bytes(vm, (proc->pc + 2), 4);
		*registre = value;
		ft_carry(proc, *registre, !(*registre));
		aux_verbose(vm, node, value);
	}
	update_pc(vm, proc, 4, 2);
	return (1);
}
