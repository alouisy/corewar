/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:17:08 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 18:21:47 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** jump if zero
*/

int	ft_zjmp(t_pvm *vm, t_list *node)
{
	int		value;
	t_process	*process;

	process = get_process(node);
	value = reverse_bytes(vm, PC + 1, 2);
	if (process->state / 2)
	{
		PC = PC + (value % IDX_MOD);
		while (PC < 0)
			PC += MEM_SIZE;
		PC %= MEM_SIZE;
		if ((vm->verbose - 1))
			ft_printf("P% 5d | zjmp %d OK\n",
					node->content_size, value);
	}
	else
	{
		if ((vm->verbose - 1))
		{
			ft_printf("P% 5d | zjmp %d FAILED\n",
					node->content_size, value);
			if (vm->verbose == 3)
				print_adv(vm, PC, 3);
		}
		PC = (PC + 3) % MEM_SIZE;
	}
	return (1);
}
