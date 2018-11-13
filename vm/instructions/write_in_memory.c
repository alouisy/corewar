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
	int 			address;
	unsigned int	tmp;
	int				color;
	int 			i;

	color = (CHAMPION(process->champ))->color;
	i = 0;
	address = process->pc + 3 + value2 % IDX_MOD;
	while (i < 4)
	{
		tmp = ((unsigned int)(address - i)) % MEM_SIZE;
		pvm->memory[tmp] = (value >> i * 8);
		pvm->mem_color[tmp] = color;
		i++;
	}
	store_buffer(pvm, address - 3, color + 8, 50);
}
