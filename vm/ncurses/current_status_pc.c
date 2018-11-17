/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/15 13:18:16 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** print information about processes in right panel
*/

static inline int	current_void(t_pvm *vm, int i, int j)
{
	while (j++ < 25)
	{
		mvwprintw(vm->nc.wright, i++, 1,
				" %10s | %5s | %4s | %6s | %5s | %5s | %4s ",
				"", "", "", "", "", "", "");
	}
	return (i);
}

static inline void	current_print(t_pvm *vm, int i, t_list *node, int k)
{
	mvwprintw(vm->nc.wright, i, 1,
			" %10d | %5d | %4d | %6d | %5d | %5d | %4d ",
			node->content_size,
			vm->champions[(int)(get_process(node))->champ_nbr].nbr,
			(get_process(node))->pc,
			(get_process(node))->opcode,
			(get_process(node))->state & 2,
			(get_process(node))->state & 1,
			vm->stack[(vm->total_cycles + k) % 1001].content_size
				- vm->total_cycles);
}

inline int			current_status_pc(t_pvm *vm, int i)
{
	t_list		*node;
	int			j;
	int			k;

	mvwprintw(vm->nc.wright, i++, 1,
			"   pid      | owner | pc   | opcode | carry | live  |  exe ");
	mvwprintw(vm->nc.wright, i++, 1,
			"____________|_______|______|________|_______|_______|______");
	k = 0;
	j = 0;
	while (k++ < 1001 && j < 40)
	{
		node = vm->stack[(vm->total_cycles + k) % 1001].next;
		while (node && j++ < 40)
		{
			current_print(vm, i, node, k);
			i++;
			node = node->next;
		}
	}
	return (current_void(vm, i, j));
}
