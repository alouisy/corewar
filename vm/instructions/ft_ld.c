/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 18:27:11 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct load
*/

static void	aux_verbose(t_pvm *vm, t_list *node, int value)
{
	if ((vm->verbose == 3))
	{
		ft_printf("P% 5d | ld %d r%d\n",
				node->content_size,
				value,
				vm->param[1]);
	}
}

int			ft_ld(t_pvm *vm, t_list *node)
{
	int		value;
	t_process	*process;

	process = get_process(node);
	value = 0;
	if (check_param(process->opcode, OCP, OP_TAB.nb_param)
		&& vm->param_type[1] == REG_CODE
		&& vm->param[1] >= 1 && vm->param[1] <= REG_NUMBER)
	{
		if (vm->param_type[0] == DIR_CODE)
			value = reverse_bytes(vm, PC + 2, 4);
		else
		{
			value = reverse_bytes(vm, PC + 2, 2);
			value %= IDX_MOD;
			value = reverse_bytes(vm, PC + value, 4);
		}
		REG(vm->param[1]) = value;
		ft_carry(process, value, !value);
		aux_verbose(vm, node, value);
	}
	if (vm->verbose == 3)
		print_adv(vm, PC, octal_shift(OCP, 4, 2));
	PC = (PC + octal_shift(OCP, 4, 2)) % MEM_SIZE;
	return (1);
}
