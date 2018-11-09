/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:17:08 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/23 17:38:13 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** jump if zero
*/

int	ft_zjmp(t_pvm *pvm, t_process *process)
{
	int		value;
	char	*str;

	value = (short int)process->param[0];
	if (process->state / 2)
	{
		str = "OK";
		process->pc += value % IDX_MOD;
		process->pc %= MEM_SIZE;
		if (process->pc < 0)
			process->pc += MEM_SIZE;
		process->pc2 = process->pc;
	}
	else
		str= "FAILED";
	if (pvm->verbose == 2)
	{
		ft_printf("P% 5d | zjmp %d %s\n", (CHAMPION(process->champ))->nbr, value, str);
	}
	return (1);
}
