/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:47:47 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 17:24:31 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** print information about processes in right panel
*/

static inline int	registre_status(t_pvm *vm, int i, t_list *node)
{
	t_process	*process;
	int			j;

	process = get_process(node);
	j = 0;
	mvwprintw(vm->nc.wright, i, 1,
			"________________________________|       ");
	mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
			"|________________________________");
	while (j < REG_NUMBER / 2)
	{
		mvwprintw(vm->nc.wright, i, 1,
				" reg[%2d]  | %18d  |", j + 1, process->r[j]);
		mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
				"| reg[%2d]   | %18d ", j + 9, process->r[j + 8]);
		j += 1;
	}
	return (i);
}

static inline int	param_status(t_pvm *vm, int i)
{
	mvwprintw(vm->nc.wright, i, 1,
			"_________________________________");
	mvwprintw(vm->nc.wright, i + 1, 1,
			"              param             |");
	mvwprintw(vm->nc.wright, i + 2, 1,
			"     0    |     1    |     2    |");
	mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
			"____________                     ");
	mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
			"|    type   |                    ");
	mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
			"| 0 | 1 | 2 |                    ");
	mvwprintw(vm->nc.wright, i, 1,
			" %8d | %8d | %8d |",
			vm->param[0],
			vm->param[1],
			vm->param[2]);
	mvwprintw(vm->nc.wright, i++, vm->nc.right_width / 2,
			"| %1d | %1d | %1d |                   ",
			vm->param_type[0],
			vm->param_type[1],
			vm->param_type[2]);
	return (i);
}

void				status_process(t_pvm *vm, int i)
{
	t_list		*node;
	int			k;

	i = current_status_pc(vm, i);
	if (i < LINES - 5)
	{
		i = LINES - 15;
		k = 0;
		while (k < 1001)
		{
			if ((node = vm->stack[(vm->total_cycles + k) % 1001].next))
				break ;
			k++;
		}
		if (node)
		{
			i = param_status(vm, i);
			registre_status(vm, i, node);
		}
	}
}
