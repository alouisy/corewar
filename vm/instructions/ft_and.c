/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/23 17:23:39 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** loqical and
*/

void	ft_and(__attribute__((unused)) t_pvm *pvm, t_process *process)
{
	int		val1;
	int		val2;

	val1 = 0;
	val2 = 0;
	if (process->param[2] >= 1 && process->param[2] <= REG_NUMBER
		&& get_prm_value(pvm, process, 0, &val1) && get_prm_value(pvm, process, 1, &val2))
	{
		process->r[process->param[2] - 1] = (val1 & val2);
		if (!(pvm->nc.ncurses) && pvm->verbose == 2)
		{
			ft_printf("P% 5d | and %d %d r%d\n", process->champ_nbr, val1, val2, process->param[2]);
		}
		if (process->r[process->param[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}
