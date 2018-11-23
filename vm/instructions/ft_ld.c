/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/23 20:15:15 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct load
*/

static void	aux_verbose(t_pvm *vm, t_list *node, int value)
{
	if (vm->verbose & 4)
	{
		ft_printf("P% 5d | ld %d r%d\n",
				node->content_size,
				value,
				vm->param[1]);
	}
}

int			ft_ld(t_pvm *vm, t_list *node)
{
	int			value;
	t_process	*process;

	process = get_process(node);
	value = 0;
	if (check_param(process->opcode, vm->ocp,
			g_op_tab[process->opcode].nb_param)
			&& is_reg(vm, 1))
	{
		if (vm->param_type[0] == DIR_CODE)
			value = reverse_bytes(vm, process->pc + 2, 4);
		else
		{
			value = reverse_bytes(vm, process->pc + 2, 2);
			value %= IDX_MOD;
			value = reverse_bytes(vm, process->pc + value, 4);
		}
		process->r[vm->param[1] - 1] = value;
		ft_carry(process, value);
		aux_verbose(vm, node, value);
	}
	update_pc(vm, process, 4, 2);
	return (1);
}
