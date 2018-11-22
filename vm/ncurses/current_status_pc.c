/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/18 13:42:01 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** print information about processes in right panel
*/

static inline int	current_void(t_pvm *vm, int i, int j)
{
	while (j++ < 40 && i < LINES - 2)
	{
		mvwprintw(vm->nc.wright, i++, 1,
				" %10s | %5s | %4s | %6s | %5s | %5s | %4s ",
				"", "", "", "", "", "", "");
	}
	return (i);
}

static inline void	current_print(t_pvm *vm, int i, t_list *node)
{
	mvwprintw(vm->nc.wright, i, 1,
			" %10d | %5d | %4d | %6d | %5d | %5d | %4d ",
			node->content_size,
			-vm->champions[(int)(get_process(node))->champ_nbr].nbr,
			(get_process(node))->pc,
			(get_process(node))->opcode,
			(get_process(node))->state & 2,
			(get_process(node))->state & 1,
			(get_process(node))->cycle_of_exe - vm->total_cycles);
}

inline int			current_status_pc(t_pvm *vm, int i)
{
	t_list		*node;
	int			j;

	mvwprintw(vm->nc.wright, i++, 1,
			"   pid      | owner | pc   | opcode | carry | live  |  exe ");
	mvwprintw(vm->nc.wright, i++, 1,
			"____________|_______|______|________|_______|_______|______");
	j = 0;
	node = vm->stack;
	while (node && j++ < 40 && i < LINES - 2)
	{
		current_print(vm, i, node);
		i++;
		node = node->next;
	}
	return (current_void(vm, i, j));
}
