/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:01:23 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/23 17:51:17 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct store
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

void	ft_st(t_pvm *pvm, t_process *process)
{
	int		value;
	int		check;

	value = 0;
	check = 0;
	if (vm->param_type[0] == REG_CODE && vm->param[0] >= 1 && vm->param[0] <= REG_NUMBER)
	{
		if (get_prm_value(pvm, process, 0, &value))
		{
			if (process->param_type[1] == REG_CODE)
			{
				if (process->param[1] >= 1 && process->param[1] <= REG_NUMBER)
				{
					check = 1;
					process->r[process->param[1] - 1] = value;
				}
				if (!(pvm->nc.ncurses) && pvm->verbose == 2)
				{
					ft_printf("P% 5d | st r%d %d\n", process->champ_nbr, process->param[0], process->param[1]);
				}
			}
			else
			{
				check = 1;
				write_in_memory(pvm, process->pc + (process->param[1] % IDX_MOD), value);
				if (!(pvm->nc.ncurses) && pvm->verbose == 2)
				{
					ft_printf("P% 5d | st r%d %d\n", process->champ_nbr, process->param[0], process->param[1]);
				}
			}
			if (check == 1 && value == 0)
				process->carry = 1;
			else if (check == 1 && value != 0)
				process->carry = 0;
		}
	}
}
