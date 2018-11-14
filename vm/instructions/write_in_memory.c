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

void	write_in_memory(t_pvm *pvm, t_process *process, int value, int value2)
{
	int 	address;
	int		tmp;
	int				color;
	int 			i;

	color = pvm->champions[(int)process->champ_nbr].color;
	i = 0;
	address = PC + (value2 % IDX_MOD) + 3;
	while (address < 0)
		address += MEM_SIZE;
	while (i < 4)
	{
		tmp = (address - i) % MEM_SIZE;
		pvm->memory[tmp] = value >> (i * 8);
		pvm->mem_color[tmp] = color;
		i++;
	}
	store_buffer(pvm, address - 3, color + 8, 50);
}
