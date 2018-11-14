/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:23 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 15:47:12 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect load
*/

void	ft_lldi(t_pvm *pvm, t_process *process)
{
	int		val1;
	int		val2;
	int		address;

	val1 = 0;
	val2 = 0;
	address = 0;
	if (process->param[2] >= 1 && process->param[2] <= REG_NUMBER
		&& get_prm_value(pvm, process, 0, &val1)
		&& get_prm_value(pvm, process, 1, &val2))
	{
/*		if (process->param_type[0] == DIR_CODE)
			val1 = (short int)val1;
		val2 = (short int)process->param[1];
*/		address = process->pc + (val1 + val2);
		if (!(pvm->nc.ncurses) && pvm->verbose == 2)
		{
			ft_printf("P% 5d | lldi %d %d r%d\n", process->champ_nbr, val1, val2, process->param[2]);
			ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", val1, val2, (val1 + val2), address);
		}
		while (address < 0)
			address += MEM_SIZE;		
		val1 = ft_strhex2dec((pvm->memory + (address % MEM_SIZE)), 4);
		process->r[process->param[2] - 1] = val1;
		if (process->r[process->param[2] - 1])
			process->carry = 0;
		else
			process->carry = 1;
	}
}
