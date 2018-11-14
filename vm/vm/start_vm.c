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
#include <time.h>

void				start_vm(t_pvm *vm)
{
	t_process	*content;
	t_list		*tmp;
	struct timespec tim, tim2;

	tim.tv_sec  = 0;
	tim.tv_nsec = 30000000L;
	while (vm->total_cycles != vm->dump && vm->processes)
	{
		vm->cur_cycle++;
		if (vm->cur_cycle == vm->cycle_to_die)
			cycle2die(vm);
		tmp = vm->processes;
		while (tmp)
		{
			content = PROCESS(tmp);
			if (content->opcode <= 0)
			{
				get_instruction(vm, content);
			}
			else
			{
				process_instruction(vm, content);
			}
			if (vm->verbose == 3 && (vm->total_cycles % 10) == 0)
			{
				system("clear");
				print_memory_2(vm, content->pc);
				nanosleep(&tim , &tim2);
			}
			if (vm->nc.ncurses)
			{
				update_process(vm, content);
			}
			tmp = tmp->next;
		}
		vm->total_cycles++;
		if (vm->nc.ncurses)
			status_game(vm);
	}
	ft_printf("end\n");
	if (vm->total_cycles == vm->dump)
		print_memory(vm);
	print_winner(vm);
}
