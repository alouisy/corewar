/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:01:23 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/09 16:04:05 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** direct store
*/

void	write_in_memory(t_pvm *pvm, t_process *process, int value, short int value2)
{
	int address;
	int	color;
	int i;

	address = process->pc + value2 % IDX_MOD;
	while (address < 0)
		address += MEM_SIZE;
	color = (CHAMPION(process->champ))->color;
	i = 0;
	while (i < 4)
	{
		pvm->memory[(address + 3 - i) % MEM_SIZE] = (value >> i * 8);
		pvm->mem_color[(address + 3 - i) % MEM_SIZE] = color;
		i++;
	}
	store_buffer(pvm, address, color + 8, 50);
}
