/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/29 19:27:32 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void		process_status(t_pvm *vm, int i)
{
	t_list		*node;
	t_process	*process;

	mvwprintw(vm->nc.wright, i++, 0,
		"| pid   | owner | pc    | pc2   | opcode | carry | live  | exe  |");
	mvwprintw(vm->nc.wright, i++, 0,
		"._______._______._______._______.________._______._______.______.");
	node = vm->processes;
	while (node)
	{
		process = PROCESS(node);
		mvwprintw(vm->nc.wright, i++, 0,
				"| %5d | %5d | %5d | %5d | %6d | %5d | %5d | %4d |",
				process->pid,
				process->champ_nbr,
				process->pc,
				process->pc2,
				process->opcode,
				process->carry,
				process->cycles_wo_live,
				process->cycle_bf_exe);
		node = node->next;
	}
}
