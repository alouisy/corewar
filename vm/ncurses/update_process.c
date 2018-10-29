/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:49:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:31:34 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static inline void	update_memory(t_pvm *vm, t_process *process)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->nc.memory[i] != vm->memory[i])
		{
			wattron(vm->nc.wleft,
					COLOR_PAIR((CHAMPION(process->champ))->color));
			mvwprintw(vm->nc.wleft,
					i / 64 + 1,
					(i % 64) * 3 + 1,
					"%.2hhx",
					vm->memory[i]);
			wattroff(vm->nc.wleft,
					COLOR_PAIR((CHAMPION(process->champ))->color));
			vm->nc.memory[i] = vm->memory[i];
		}
		i++;
	}
}

static inline void	update_pc(t_pvm *vm, t_process *process)
{
	int	i;

	i = 4;
	if (process->cycle_bf_exe == 1)
		i = 0;
	wattron(vm->nc.wleft, COLOR_PAIR((CHAMPION(process->champ))->color + i));
	mvwprintw(vm->nc.wleft,
			process->pc / 64 + 1,
			(process->pc % 64) * 3 + 1, "%.2hhx",
			vm->memory[process->pc]);
	wattroff(vm->nc.wleft, COLOR_PAIR((CHAMPION(process->champ))->color + i));
}

void				update_process(t_pvm *vm, t_process *process)
{
	update_pc(vm, process);
	update_memory(vm, process);
}
