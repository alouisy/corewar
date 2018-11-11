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

int	ft_add(__attribute__((unused)) t_pvm *vm, t_process *process)
{
	int		i;
	int 	error;

	i = -1;
	error = 0;
	while (++i < 3)
		if (vm->param[i] < 1 || vm->param[i] > REG_NUMBER)
			error = 1;
	if (!error)
	{
		process->r[vm->param[2] - 1] = process->r[vm->param[0] - 1] +
			process->r[vm->param[1] - 1];
		if (vm->verbose == 2)
		{
			ft_printf("P% 5d | add r%d r%d r%d\n",
					(CHAMPION(process->champ))->nbr, vm->param[0],
					vm->param[1], vm->param[2]);
		}
		ft_carry(process, process->r[vm->param[2] - 1],
				!(process->r[vm->param[2] - 1]));
	}
	return (1);
}
