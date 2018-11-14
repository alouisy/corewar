/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:54:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 15:45:58 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** indirect store
*/

static void	write_in_memory(t_pvm *pvm, int address, int value)
{
	while (address < 0)
		address += MEM_SIZE;
	pvm->memory[(address + 3) % MEM_SIZE] = (value >> 0);
	pvm->memory[(address + 2) % MEM_SIZE] = (value >> 8);
	pvm->memory[(address + 1) % MEM_SIZE] = (value >> 16);
	pvm->memory[(address + 0) % MEM_SIZE] = (value >> 24);
}

void	ft_sti(t_pvm *pvm, t_process *process)
{
	int		val1;
	int		val2;
	int		val3;
	int		address;

	val1 = 0;
	val2 = 0;
	val3 = 0;
	address = 0;
	if (process->param[0] >= 1 && process->param[0] <= REG_NUMBER
		&& get_prm_value(pvm, process, 1, &val1) && get_prm_value(pvm, process, 2, &val2))
	{
/*		if (process->param_type[1] == DIR_CODE)
			val1 = (short int)val1;
		val2 = (short int)process->param[2];
*/		address = process->pc + ((val1 + val2) % IDX_MOD);
		if (!(pvm->nc.ncurses) && pvm->verbose == 2)
		{
			ft_printf("P% 5d | sti r%d %d %d\n", process->champ_nbr, process->param[0], val1, val2);
			ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", val1, val2, (val1 + val2), address);
		}
	//	printf("pc = %d address sti = %d val1 = %d val2 = %d\n", process->pc, address, val1, val2);
		val3 = process->r[process->param[0] - 1];
		write_in_memory(pvm, address, val3);
		if (process->r[process->param[0] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
}
