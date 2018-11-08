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

void	ft_st(t_pvm *pvm, t_process *process)
{
	int		value;
	int		check;

	value = 0;
	check = 0;
	if (get_prm_value(pvm, process, 0, &value))
	{
		if (process->param_type[1] == REG_CODE)
		{
			if (process->param[1] >= 1 && process->param[1] <= REG_NUMBER)
			{
				check = 1;
				process->r[process->param[1] - 1] = value;
			}
			if (!(pvm->nc.ncurses) && pvm->verbose)
			{
				ft_printf("P% 5d | st r%d %d\n", (CHAMPION(process->champ))->nbr, process->param[0], process->param[1]);
			}
		}
		else
		{
			check = 1;
			write_in_memory(pvm, process, value, (short int)process->param[1]);
			if (!(pvm->nc.ncurses) && pvm->verbose)
			{
				ft_printf("P% 5d | st r%d %d\n", (CHAMPION(process->champ))->nbr, process->param[0], ((short int)process->param[1]));
			}
		}
		if (check == 1 && value == 0)
			process->carry = 1;
		else if (check == 1 && value != 0)
			process->carry = 0;
	}
}
