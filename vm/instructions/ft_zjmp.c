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

int	ft_zjmp(t_pvm *vm, t_process *process)
{
	int		value;
	char	*str;

	value = reverse_bytes(vm, process->pc + 1, 2);
	if (vm->verb == 3)
		print_adv(vm, process->pc, 3);
	if (process->state / 2)
	{
		str = "OK";
		process->pc = (unsigned int)(process->pc + (value % IDX_MOD)) % MEM_SIZE;
	}
	else
	{
		str = "FAILED";
		process->pc = (process->pc + 3) % MEM_SIZE;
	}
	if (vm->verbose == 2)
	{
		ft_printf("P% 5d | zjmp %d %s\n", (CHAMPION(process->champ))->nbr, value, str);
	}

	return (1);
}
