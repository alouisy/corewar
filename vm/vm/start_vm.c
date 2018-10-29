/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/29 18:40:56 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static inline void	print_winner(t_pvm *vm)
{
	t_list	*champ;

	champ = vm->champions;
	while (champ)
	{
		if ((CHAMPION(champ))->l_live >= vm->last_live)
			break ;
		champ = champ->next;
	}
	if (vm->nc.ncurses)
		clear();
	ft_printf("le joueur %d(%s) a gagne\n", (CHAMPION(champ))->nbr, (CHAMPION(champ))->header.prog_name);
}

void	update_process(t_pvm *vm, t_process *process)
{
	int	i;

	i = 4;
	if (process->cycle_bf_exe == 1)
		i = 0;
	wattron(vm->nc.wleft, COLOR_PAIR((CHAMPION(process->champ))->color + i));
	mvwprintw(vm->nc.wleft, process->pc / 64 + 1, (process->pc % 64) * 3 + 1, "%.2hhx", vm->memory[process->pc]);
	wattroff(vm->nc.wleft, COLOR_PAIR((CHAMPION(process->champ))->color + i));
}

void				start_vm(t_pvm *vm)
{
	t_process	*content;
	t_list		*tmp;

	while (vm->total_cycles != vm->dump && vm->processes)
	{
		vm->cur_cycle++;
		if (vm->cur_cycle == vm->cycle_to_die)
			cycle2die(vm);
		tmp = vm->processes;
		while (tmp)
		{
			content = PROCESS(tmp);
			if (content->opcode == -1)
				get_instruction(vm, content);
			else
				process_instruction(vm, content);
			update_process(vm, content);
			tmp = tmp->next;
		}
		vm->total_cycles++;
		if (vm->nc.ncurses)
			game_status(vm);
	}
	print_winner(vm);
}
