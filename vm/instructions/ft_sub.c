/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:09:45 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/19 13:26:17 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** aritmetical substraction
*/

static void	aux_verbose(t_pvm *vm, t_process *process)
{
	if (vm->verbose == 2)
	{
		ft_printf("P% 5d | sub r%d r%d r%d\n",
				(CHAMPION(process->champ))->nbr,
				vm->param[0],
				vm->param[1],
				vm->param[2]);
	}
	else if (vm->verb == 3)
		print_adv(vm, process->pc, octal_shift(process->ocp, 4, 3));
}

int	ft_sub(t_pvm *vm, t_process *process)
{
	int		i;
	int 	error;

	i = -1;
	error = 0;
	if (check_param(process->opcode, process->ocp, g_op_tab[process->opcode].nb_param))
	{
		while (++i < 3)
		{
			if (vm->param[i] < 1 || vm->param[i] > REG_NUMBER)
				error = 1;
		}
		if (!error)
		{
			process->r[vm->param[2] - 1] = process->r[vm->param[0] - 1]
				- process->r[vm->param[1] - 1];
			ft_carry(process, process->r[vm->param[2] - 1], !(process->r[vm->param[2] - 1]));
		}
	}
	aux_verbose(vm, process);
	process->pc = (process->pc + octal_shift(process->ocp, 4, 3)) % MEM_SIZE;
	return (1);
}
