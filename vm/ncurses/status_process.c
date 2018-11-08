/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/07 20:44:27 by jgroc-de         ###   ########.fr       */
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
		mvwprintw(vm->nc.wright, i, 1,
				"__________|_____________________|       ");
		mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
				"|___________|____________________");
		while (j < REG_NUMBER)
		{
			mvwprintw(vm->nc.wright, i, 1,
					" reg[%2d]  | %18d  |", j, process->r[j]);
			mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
					"| reg[%2d]   | %18d ", j + 1, process->r[j +1]);
			j += 2;
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
		mvwprintw(vm->nc.wright, i, 1,
				"__________|__________|__________|");
		mvwprintw(vm->nc.wright, i + 1, 1,
				"              param             |");
		mvwprintw(vm->nc.wright, i + 2, 1,
				"     0    |     1    |     2    |");
		mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
				"|___________|                    ");
		mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
				"|    type   |                    ");
		mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
				"| 0 | 1 | 2 |                    ");
		mvwprintw(vm->nc.wright, i, 1,
				" %8d | %8d | %8d |",
				process->param[0],
				process->param[1],
				process->param[2]);
		mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
				"| %1d | %1d | %1d |                   ",
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

	mvwprintw(vm->nc.wright, i++, 1,
			"   pid      | owner | pc   | pc2  | opcode | carry | live  |  exe ");
	mvwprintw(vm->nc.wright, i++, 1,
			"____________|_______|______|______|________|_______|_______|______");
	k = 0;
	j = 0;
	while (k < 1001)
	{
		node = vm->stack[(vm->total_cycles + k) % 1001].next;
		if (k > 1 && j > 40)
			break;
		while (node)
		{
			process = PROCESS(node);
			if (j < 40)
			{
				mvwprintw(vm->nc.wright, i++, 1,
						" %10d | %5d | %5d | %5d | %6d | %5d | %5d | %4d ",
						node->content_size,
						(CHAMPION(process->champ))->nbr,
						process->pc,
						process->pc2,
						process->opcode,
						process->state / 2 ? 1 : 0,
						process->state % 2 ? 1 : 0,
						process->cycle_of_exe - vm->total_cycles);
			}
			color = (CHAMPION(process->champ))->color + 4;
			if (k == 0)
				store_buffer(vm, process->pc, color, process->cycle_of_exe);
			node = node->next;
			j++;
		}
		k++;
	}
	while (j++ < 25)
	{
		mvwprintw(vm->nc.wright, i++, 1,
				" %6s | %5s | %5s | %5s | %6s | %5s | %5s | %6s ",
				"", "", "", "", "", "", "", ""); 
	}
	return (i);
}

void		status_process(t_pvm *vm, int i)
{
	i = current_status_pc(vm, i);
	if (i < LINES - 5)
	{
		i = LINES - 15;
		i = param_status(vm, i);
		registre_status(vm, i);
	}
}
