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

void	start_vm(t_pvm *vm)
{
	t_process	*content;
	t_list		*node;
	t_list		*save;

	while (vm->total_cycles != vm->dump)
	{
		if (vm->total_cycles >= vm->cycle_to_die)
			cycle2die(vm, 0);
		if (vm->c2d < 0)
			break ;
		node = vm->stack[(vm->total_cycles) % 1001].next;
		vm->stack[(vm->total_cycles) % 1001].next = NULL;
		vm->total_cycles++;
		while (node)
		{
			save = node->next;
			content = PROCESS(node);
			if (content->opcode == 0)
			{
				get_instruction(vm, content);
			}
			else if (!process_instruction(vm, content))
				break ;
			update_stack(vm, vm->total_cycles, node);
/*			else if (content->opcode != 0)
			{
				chck = process_instruction(vm, content);
				if (!chck)
					break ;
			}
			if (chck != 2)
				update_stack(vm, vm->total_cycles, node);
*/			if (vm->verbose == 1)
				status_game(vm);
			node = save;
		}
	//	if (vm->verbose == 1)
	//		status_game(vm);
		if (vm->c2d < 0)
			break ;
	}
	cycle2die(vm, 1);
	if (vm->verbose != 1)
		ft_printf("end\n");
	if (vm->total_cycles == vm->dump)
		print_memory(vm);
	print_winner(vm);
}
