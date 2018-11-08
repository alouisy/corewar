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

int	ft_sub(__attribute__((unused)) t_pvm *pvm, t_process *process)
{
	int		i;
	int 	error;

	i = -1;
	error = 0;
	while (++i < 3)
		if (process->param[i] < 1 || process->param[i] > REG_NUMBER)
			error = 1;
	if (!error)
	{
		process->r[process->param[2] - 1] = process->r[process->param[0] - 1]
		- process->r[process->param[1] - 1];
		if (pvm->verbose == 2)
		{
			ft_printf("P% 5d | sub r%d r%d r%d\n", (CHAMPION(process->champ))->nbr, process->param[0], process->param[1], process->param[2]);
		}
		ft_carry(process, process->r[process->param[2] - 1], !(process->r[process->param[2] - 1]));
	}
	return (1);
}
