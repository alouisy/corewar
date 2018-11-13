/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:13:08 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/20 18:09:09 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** logical or
*/

static void	aux_verbose(t_pvm *vm, t_process *process,  int val1, int val2)
{
	if (vm->verbose == 2)
	{
		ft_printf("P% 5d | or %d %d r%d\n",
				(CHAMPION(process->champ))->nbr,
				val1,
				val2,
				vm->param[2]);
	}
	else if (vm->verb == 3)
		print_adv(vm, process->pc, octal_shift(process->ocp, 4, 3));
}

int	ft_or(t_pvm *vm, t_process *process)
{
	return (aux_andorxor(vm, process, 2, &aux_verbose));
}
