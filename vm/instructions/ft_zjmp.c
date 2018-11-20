/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:17:08 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/17 16:10:58 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** jump if zero
*/

int	ft_zjmp(t_pvm *vm, t_list *node)
{
	int			value;
	t_process	*process;

	process = get_process(node);
	value = reverse_bytes(vm, process->pc + 1, 2);
	if ((process->state / 2))
	{
		process->pc = (process->pc + (value % IDX_MOD)) % MEM_SIZE;
		if (process->pc < 0)
			process->pc += MEM_SIZE;
		if (vm->verbose & 4)
			ft_printf("P% 5d | zjmp %d OK\n", node->content_size, value);
	}
	else
	{
		if (vm->verbose & 4)
			ft_printf("P% 5d | zjmp %d FAILED\n", node->content_size, value);
		if (vm->verbose & 16)
			print_adv(vm, process->pc, 3);
		process->pc += 3;
	}
	return (1);
}
