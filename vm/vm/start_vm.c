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
	t_list *save;

	node = vm->stack[(vm->total_cycles + cycles) % 1001].next;
	save = &(vm->stack[(vm->total_cycles + cycles) % 1001]);
	while (node && node->next && (PROCESS(node))->pid > (PROCESS(tmp))->pid)
	{
		save = node;
		node = node->next;
	}
	tmp->next = save->next;
	save->next = tmp;
}

void	start_vm(t_pvm *vm)
{
	t_process	*content;
	t_list		*tmp;
	t_list		*save;
	t_list		*next;

	while (vm->total_cycles != vm->dump && vm->nb_process)
	{
		if (vm->cur_cycle >= vm->cycle_to_die)
			cycle2die(vm);
		if (vm->cycle_to_die < 0)
			break ;
		tmp = vm->stack[(vm->total_cycles) % 1001].next;
		save = &(vm->stack[(vm->total_cycles) % 1001]);
		while (tmp)
		{
			content = PROCESS(tmp);
			next = tmp->next;
			if (content->opcode <= 0)
			{
				get_instruction(vm, content);
				save->next = save->next->next;
				update_stack(vm, content->cycle_bf_exe, tmp);
			}
			else
			{
				process_instruction(vm, content);
				save->next = save->next->next;
				update_stack(vm, content->cycle_bf_exe, tmp);
			}
			tmp = next;
		}
		vm->cur_cycle++;
		vm->total_cycles++;
		if (vm->nc.ncurses)
			status_game(vm);
	}
	ft_printf("end\n");
	if (vm->total_cycles == vm->dump)
		print_memory(vm);
	print_winner(vm);
}
