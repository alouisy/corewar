/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:47:27 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 18:29:37 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect load
*/

static void	aux_verbose(t_pvm *vm, t_list *node, int val[2], __attribute__((unused)) int address)
{
	t_process	*process;

	process = get_process(node);
	if ((vm->verbose - 1))
	{
		ft_printf("P% 5d | ldi %d %d r%d\n",
				node->content_size,
				val[0],
				val[1],
				vm->param[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
				val[0],
				val[1],
				val[0] + val[1],
				address);
		if (vm->verbose == 3)
			print_adv(vm, PC, octal_shift(OCP, 2, 3));
	}
}

int			ft_ldi(t_pvm *vm, t_list *node)
{
	int		val[2];
	int		address;
	t_process	*process;

	process = get_process(node);
	val[0] = 0;
	val[1] = 0;
	address = 0;
	if (check_param(process->opcode, OCP, OP_TAB.nb_param))
	{
		if (vm->param_type[2] == 1
			&& vm->param[2] >= 1 && vm->param[2] <= REG_NUMBER
			&& get_prm_value(vm, process, 0, &val[0])
			&& get_prm_value(vm, process, 1, &val[1]))
		{
			address = PC + ((val[0] + val[1]) % IDX_MOD);
			REG(vm->param[2]) = reverse_bytes(vm, address, 4);
		}
	}
	aux_verbose(vm, node, val, address);
	PC = (PC + octal_shift(OCP, 2, 3)) % MEM_SIZE;
	return (1);
}
