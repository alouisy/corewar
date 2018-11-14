/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:16:15 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:21:14 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static void	aux_verbose(t_pvm *vm, t_process *process)
{
	if (vm->verbose == 2)
	{
		ft_printf("P% 5d | live %d\n",
				vm->champions[(int)process->champ_nbr].nbr,
				vm->param[0]);
	}
	else if (vm->verbose == 3)
		print_adv(vm, PC, 5);
}

int	ft_live(t_pvm *vm, t_process *process)
{
	int nbr;

	if (!(process->state % 2))
		process->state += 1;
	vm->sum_lives++;
	vm->param[0] = reverse_bytes(vm, PC + 1, 4);
	if ((nbr = ft_find_champ(vm, vm->param[0])) != -1)
	{
		vm->champions[nbr].nb_live++;
		vm->champions[nbr].l_live = vm->total_cycles;
		vm->last_live = vm->total_cycles;
	}
	aux_verbose(vm, process);
	PC += 5;
	PC %= MEM_SIZE;
	return (1);
}
