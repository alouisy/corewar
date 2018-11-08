/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/29 19:01:00 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	update_stack(t_pvm *vm, int cycles, t_list *tmp)
{
	t_list *node;

	node = (t_list*)(vm->stack[(cycles) % 1001].content);
	tmp->next = NULL;
	if (node)
		node->next = tmp;
	else
		vm->stack[(cycles) % 1001].next = tmp;
	vm->stack[(cycles) % 1001].content = tmp;
}

void	start_vm(t_pvm *vm)
{
	t_process	*content;
	t_list		*tmp;
	t_list		*save;

	while (vm->total_cycles != vm->dump)
	{
		if (vm->total_cycles >= vm->cycle_to_die)
			cycle2die(vm);
		if (vm->c2d < 0)
			break ;
		tmp = vm->stack[(vm->total_cycles) % 1001].next;
		vm->stack[(vm->total_cycles) % 1001].next = NULL;
		vm->total_cycles++;
		while (tmp)
		{
			save = tmp->next;
			content = PROCESS(tmp);
			if (content->opcode <= 0)
			{
				get_instruction(vm, content);
			}
			else
			{
				process_instruction(vm, content);
			}
			update_stack(vm, content->cycle_of_exe, tmp);
			tmp = save;
		}
		if (vm->nc.ncurses)
			status_game(vm);
	}
	if (!vm->nc.ncurses)
		ft_printf("end\n");
	if (vm->total_cycles == vm->dump)
		print_memory(vm);
	print_winner(vm);
}
