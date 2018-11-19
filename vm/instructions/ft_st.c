/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:01:23 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/17 15:34:28 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct store
*/

static void	aux_verbose(t_pvm *vm, t_list *node)
{
	if (vm->verbose & 4)
	{
		ft_printf("P% 5d | st r%d %d\n",
				node->content_size,
				vm->param[0],
				vm->param[1]);
	}
}

int			ft_st(t_pvm *vm, t_list *node)
{
	t_process	*process;
	int			*registre;
	
	process = get_process(node);
	registre = reg(process, vm->param[0]);
	if (check_param(process->opcode, vm->ocp, g_op_tab[process->opcode].nb_param)
			&& is_reg(vm, 0))
	{
		if (is_reg(vm, 1))
		{
			process->r[vm->param[1] - 1] = *registre;
			aux_verbose(vm, node);
		}
		else if (vm->param_type[1] == IND_CODE)
		{
			vm->param[1] = reverse_bytes(vm, process->pc + 3, 2);
			write_in_memory(vm, process, *registre, vm->param[1]);
			aux_verbose(vm, node);
		}
	}
	update_pc(vm, process, 4, 2);
	return (1);
}
