/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:27:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/24 17:27:40 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct load
*/

int	ft_ld(__attribute__((unused)) t_pvm *pvm, t_process *process)
{
	int		value;

	value = 0;
	if (process->param[1] >= 1 && process->param[1] <= REG_NUMBER
		&& get_prm_value(pvm, process, 0, &value))
	{
		process->r[process->param[1] - 1] = value;
		if (pvm->verbose == 2)
		{
			ft_printf("P% 5d | ld %d r%d\n", (CHAMPION(process->champ))->nbr, value, process->param[1]);
		}
		ft_carry(process, value, !value);
	}
	return (1);
}
