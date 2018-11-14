/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:33 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:18:45 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** fork
*/

int		ft_fork(t_pvm *vm, t_process *process)
{
	int value;

	value = vm->param[0];
	if (!aux_fork(vm, process, value % IDX_MOD))
		return (0);
	if (vm->verbose == 2)
	{
		ft_printf("P% 5d | fork %d (%d)\n",
				vm->champions[(int)process->champ_nbr].nbr,
				value,
				(process->pc + (value % IDX_MOD)));
	}
	else if (vm->verbose == 3)
		print_adv(vm, process->pc, 3);
	process->pc = (process->pc + 3) % MEM_SIZE;
	return (1);
}
