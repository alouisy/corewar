/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/30 17:14:12 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** print information about processes in right panel
*/

int registre_status(t_pvm *vm, int i)
{
	int j;
	t_process	*process;
	t_list		*node;
	int k;
	
	k = 0;
	while (k < 1001)
	{
		if ((node = vm->stack[(vm->total_cycles + k) % 1001].next))
			break ;
		k++;
	}
	if (node)
	{
		process = PROCESS(node);	
		j = 0;
		while (j < REG_NUMBER)
		{
			mvwprintw(vm->nc.wright, i++, 0,
					"| reg %2d | %10d |", j, process->r[j]);
			j++;
		}
	}
	return (i);
}

int	param_status(t_pvm *vm, int i)
{
	t_process	*process;
	t_list		*node;
	int k;
	
	k = 0;
	while (k < 1001)
	{
		if ((node = vm->stack[(vm->total_cycles + k) % 1001].next))
			break ;
		k++;
	}
	if (node)
	{
		process = PROCESS(node);
		mvwprintw(vm->nc.wright, i++, 0,
				"| param 0 | param 1 | param 2 |");
		mvwprintw(vm->nc.wright, i++, 0,
				"| %7d | %7d | %7d |",
				process->param[0],
				process->param[1],
				process->param[2]);
		mvwprintw(vm->nc.wright, i++, 0,
				"| type0 | type1 | type2 |");
		mvwprintw(vm->nc.wright, i++, 0,
				"| %5d | %5d | %5d |",
				process->param_type[0],
				process->param_type[1],
				process->param_type[2]);
	}
	return (i);
}

static inline int	current_status_pc(t_pvm *vm, int i)
{
	t_list		*node;
	int			color;
	t_process	*process;
	int			j;
	int			k;

	mvwprintw(vm->nc.wright, i++, 0,
		"| pid    | owner | pc    | pc2   | opcode | carry | live  |   exe  |");
	mvwprintw(vm->nc.wright, i++, 0,
			"._______._______._______._______.________._______._______.______.");
	k = 0;
	j = 0;
	while (k < 1001)
	{
		node = vm->stack[(vm->total_cycles + k) % 1001].next;
		while (node)
		{
			process = PROCESS(node);
			if (j < 40)
			{
				mvwprintw(vm->nc.wright, i++, 0,
						"| %6d | %5d | %5d | %5d | %6d | %5d | %5d | %6d |",
						process->pid,
						(CHAMPION(process->champ))->nbr,
						process->pc,
						process->pc2,
						process->opcode,
						process->carry,
						process->cycles_wo_live,
						process->cycle_bf_exe);
			}
			color = (CHAMPION(process->champ))->color + 4;
			if (k == 0)
				store_buffer(vm, process->pc, color, process->cycle_bf_exe);
			node = node->next;
			j++;
		}
		k++;
	}
	return (i);
}

void		status_process(t_pvm *vm, int i)
{
	i = current_status_pc(vm, i);
	if (i < LINES - 5)
	{
		i = param_status(vm, i + 1);
		registre_status(vm, i + 1);
	}
}
