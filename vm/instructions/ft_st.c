/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:01:23 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/23 17:51:17 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct store
*/

static void	aux_verbose(t_pvm *vm, t_process *process)
{
	if ((vm->verbose - 1))
	{
		ft_printf("P% 5d | st r%d %d\n",
				vm->champions[(int)process->champ_nbr].nbr,
				vm->param[0],
				vm->param[1]);
		if (vm->verbose == 3)
			print_adv(vm, PC, octal_shift(OCP, 4, 2));
	}
}

int	ft_st(t_pvm *vm, t_process *process)
{
	if (check_param(process->opcode, OCP, OP_TAB.nb_param))
	{
		if (vm->param_type[0] == REG_CODE && vm->param[0] >= 1 && vm->param[0] <= REG_NUMBER)
		{
			if (vm->param_type[1] == REG_CODE && vm->param[1] >= 1 && vm->param[1] <= REG_NUMBER)
			{
				REG(vm->param[1]) = REG(vm->param[0]);
				ft_carry(process, vm->param[0], !vm->param[0]);
			}
			else if (vm->param_type[1] == IND_CODE)
			{
				vm->param[1] = reverse_bytes(vm, PC + 3, 2);
				write_in_memory(vm, process, REG(vm->param[0]), vm->param[1]);
				ft_carry(process, REG(vm->param[0]), !(REG(vm->param[0])));
			}
		}
	}
	aux_verbose(vm, process);
	PC = (PC + octal_shift(OCP, 4, 2)) % MEM_SIZE;
	return (1);
}
