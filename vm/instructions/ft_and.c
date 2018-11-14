/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 15:19:53 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** logical and
*/

static void	aux_verbose(t_pvm *vm, t_process *process,  int val1, int val2)
{
	if ((vm->verbose - 1))
	{
		ft_printf("P% 5d | and %d %d r%d\n",
				(CHAMPION(process->champ))->nbr,
				val1,
				val2,
				vm->param[2]);
		if (vm->verbose == 3)
			print_adv(vm, process->pc, octal_shift(process->ocp, 4, 3));
	}
}

int	ft_and(t_pvm *vm, t_process *process)
{
	return (aux_andorxor(vm, process, 1, &aux_verbose));
}
