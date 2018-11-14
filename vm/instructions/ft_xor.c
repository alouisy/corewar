/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:13:37 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/20 18:09:36 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** logical XOR
*/

static void	aux_verbose(t_pvm *vm, t_process *process,  int val1, int val2)
{
	if ((vm->verbose - 1))
	{
		ft_printf("P% 5d | xor %d %d r%d\n",
				vm->champions[(int)process->champ_nbr].nbr,
				val1,
				val2,
				vm->param[2]);
		if (vm->verbose == 3)
			print_adv(vm, process->pc, octal_shift(vm->ocp, 4, 3));
	}
}

int	ft_xor(t_pvm *vm, t_process *process)
{
	return (aux_andorxor(vm, process, 3, &aux_verbose));
}
