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

int	ft_st(t_pvm *vm, t_process *process)
{
	int		value;
	int		check;

	value = 0;
	check = 0;
	if (get_prm_value(vm, process, 0, &value))
	{
		if (vm->param_type[1] == REG_CODE)
		{
			if (vm->param[1] >= 1 && vm->param[1] <= REG_NUMBER)
			{
				check = 1;
				process->r[vm->param[1] - 1] = value;
				if (vm->verbose == 2)
					ft_printf("P% 5d | st r%d %d\n", (CHAMPION(process->champ))->nbr, vm->param[0], vm->param[1]);
			}
		}
		else
		{
			check = 1;
			write_in_memory(vm, process, value, (short int)vm->param[1]);
			if (vm->verbose == 2)
			{
				ft_printf("P% 5d | st r%d %d\n", (CHAMPION(process->champ))->nbr, vm->param[0], ((short int)vm->param[1]));
			}
		}
		if (check)
			ft_carry(process, value, !value);
	}
	return (1);
}
