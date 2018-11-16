/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 18:29:00 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** long fork
*/

int		ft_lfork(t_pvm *vm, t_list *node)
{
	int value;
	t_process	*process;

	process = get_process(node);
	value = reverse_bytes(vm, PC + 1, 2);
	if (!aux_fork(vm, node, value))
		return (0);
	if ((vm->verbose == 3))
	{
		ft_printf("P% 5d | lfork %d (%d)\n",
				node->content_size,
				value,
				(PC + value));
		if (vm->verbose == 3)
			print_adv(vm, PC, 3);
	}
	PC = (PC + 3) % MEM_SIZE;
	return (1);
}
