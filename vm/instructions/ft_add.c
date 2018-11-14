/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:03:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:19:26 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** aritmetical addition
*/

static void	aux_verbose(t_pvm *vm, t_process *process)
{
	if (vm->verbose == 2)
	{
		ft_printf("P% 5d | add r%d r%d r%d\n",
				vm->champions[(int)process->champ_nbr].nbr,
				vm->param[0],
				vm->param[1],
				vm->param[2]);
	}
	else if (vm->verbose == 3)
		print_adv(vm, process->pc, octal_shift(vm->ocp, 4, 3));
}

int	ft_add(t_pvm *vm, t_process *process)
{
	int		i;
	int 	error;

	i = -1;
	error = 0;
	if (check_param(process->opcode, vm->ocp, g_op_tab[process->opcode].nb_param))
	{
		while (++i < 3)
			if (vm->param[i] < 1 || vm->param[i] > REG_NUMBER)
				error = 1;
		if (!error)
		{
			process->r[vm->param[2]] = process->r[vm->param[0]] +
				process->r[vm->param[1]];
			ft_carry(process, process->r[vm->param[2]],
					!(process->r[vm->param[2]]));
		}
	}
	aux_verbose(vm, process);
	process->pc = (process->pc + octal_shift(vm->ocp, 4, 3)) % MEM_SIZE;
	return (1);
}
