/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/09 15:09:18 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int do_it(t_pvm *vm, t_list *node)
{
	t_list	*save;
	t_process	*content;
	int			cycle;

	while (node)
	{
		save = node->next;
		content = PROCESS(node);
		if (content->opcode == 0)
		{
			cycle = get_opcode(vm, content);
		}
		else
		{
			if (!(cycle = process_instruction(vm, content)))
				return (0);
		}
		update_stack(vm, cycle, node);
		node = save;
	}
	return (1);
}

int	start_vm(t_pvm *vm)
{
	t_list		*node;

	while (vm->total_cycles != vm->dump)
	{
		if (vm->total_cycles >= vm->cycle_to_die)
			cycle2die(vm, 0);
		if (vm->c2d < 0)
			break ;
		node = vm->stack[(vm->total_cycles) % 1001].next;
		vm->stack[(vm->total_cycles) % 1001].next = NULL;
		vm->stack[(vm->total_cycles) % 1001].content = NULL;
		vm->total_cycles++;
		if (!do_it(vm, node))
			break ;
		if (vm->verbose == 1)
			status_game(vm);
	}
	cycle2die(vm, 1);
	if (vm->verbose != 1)
		ft_printf("end\n");
	if (vm->total_cycles == vm->dump)
		print_memory(vm);
	print_winner(vm);
	return (1);
}
