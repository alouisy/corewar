/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:21:27 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long direct load
*/

int	ft_lld(t_pvm *vm, t_process *process)
{
	int		value;
//	int		address;

	value = 0;
//	address = 0;
	if (check_param(process->opcode, process->ocp, g_op_tab[process->opcode].nb_param))
	{	
		if (vm->param[1] >= 1 && vm->param[1] <= REG_NUMBER)
		{
			if (vm->param_type[0] == IND_CODE)
				value = reverse_bytes(vm, (process->pc + vm->param[0]), 2);
			else if (vm->param_type[0] == DIR_CODE)
				value = reverse_bytes(vm, (process->pc + 2), 4);
	//		address = process->pc + value;
	//		while (address < 0)
	//			address += MEM_SIZE;
			process->r[vm->param[1] - 1] = value;
			if (vm->verbose == 2)
			{
				ft_printf("P% 5d | lld %d r%d\n",
						(CHAMPION(process->champ))->nbr,
						value,
						vm->param[1]);
			}
			ft_carry(process, process->r[vm->param[2] - 1], !(process->r[vm->param[2] - 1]));
		}
	}
	if (vm->verb == 3)
		print_adv(vm, process->pc, octal_shift(process->ocp, 4, 2));
	process->pc = (process->pc + octal_shift(process->ocp, 4, 2)) % MEM_SIZE;
	return (1);
}
/*
int	ft_lld(t_pvm *vm, t_process *process)
{
	int		value;
//	int		address;

	value = 0;
//	address = 0;
	if (vm->param[1] >= 1 && vm->param[1] <= REG_NUMBER
		&& get_prm_value(vm, process, 0, &value))
	{
		if (vm->param_type[0] == IND_CODE)
			value = reverse_bytes(vm, (process->pc + vm->param[0]), 2);
		else if (vm->param_type[0] == DIR_CODE)
			value = reverse_bytes(vm, (process->pc + 2), 4);
//		address = process->pc + value;
//		while (address < 0)
//			address += MEM_SIZE;
		process->r[vm->param[1] - 1] = value;
		if (vm->verbose == 2)
		{
			ft_printf("P% 5d | lld %d r%d\n",
					(CHAMPION(process->champ))->nbr,
					value,
					vm->param[1]);
		}
		ft_carry(process, process->r[vm->param[2] - 1], !(process->r[vm->param[2] - 1]));
	}
	return (1);
}
*/