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

int	ft_or(__attribute__((unused)) t_pvm *pvm, t_process *process)
{

	int		val1;
	int		val2;

	val1 = 0;
	val2 = 0;
	if (process->param[2] >= 1 && process->param[2] <= REG_NUMBER
		&& get_prm_value(pvm, process, 0, &val1) && get_prm_value(pvm, process, 1, &val2))
	{
		process->r[process->param[2] - 1] = (val1 | val2);
		if (pvm->verbose == 2)
		{
			ft_printf("P% 5d | or %d %d r%d\n", (CHAMPION(process->champ))->nbr, val1, val2, process->param[2]);
		}
		ft_carry(process, process->r[process->param[2] - 1], !(process->r[process->param[2] - 1]));
	}
	return (1);
}
