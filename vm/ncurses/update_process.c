/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:49:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/30 18:33:28 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	ft_del1(void *content, size_t size)
{
	(void)(content);
	(void)size;
}

static inline void	update_buffer(t_pvm *vm)
{
	int		i;
	t_list	*node;
	t_list	*todel;

	node = vm->nc.buffer;
	todel = NULL;
	while (node)
	{
		if ((get_buffer(node))->cycle)
			(get_buffer(node))->cycle--;
		else
		{
			i = (get_buffer(node))->i;
			wattron(vm->nc.wleft, COLOR_PAIR((get_buffer(node))->color));
			mvwprintw(vm->nc.wleft,
					i / 64 + 1,
					(i % 64) * 3 + 1,
					"%.2hhx",
					vm->memory[i]);
			wattroff(vm->nc.wleft, COLOR_PAIR((get_buffer(node))->color));
			todel = ft_lstpop(node, vm->nc.buffer);
		}
		node = node->next;
		if (todel)
		{
			//ft_lstdelone(&todel, &ft_del1);
			//free(todel);
			todel = NULL;
		}
	}
}

static inline int	update_memory(t_pvm *vm, t_process *process)
{
	int			i;
	t_list 		*node;
	t_buffer	mem;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->nc.memory[i] != vm->memory[i])
		{
			wattron(vm->nc.wleft,
					COLOR_PAIR((CHAMPION(process->champ))->color + 8));
			mvwprintw(vm->nc.wleft,
					i / 64 + 1,
					(i % 64) * 3 + 1,
					"%.2hhx",
					vm->memory[i]);
			mem.i = i;
			mem.color = (CHAMPION(process->champ))->color;
			mem.cycle = 10;
			if (!(node = ft_lstnew(&mem, sizeof(mem))))
				return (0);
			ft_lstadd(&(vm->nc.buffer), node);
			wattroff(vm->nc.wleft,
					COLOR_PAIR((CHAMPION(process->champ))->color + 8));
			vm->nc.memory[i] = vm->memory[i];
		}
		i++;
	}
	return (1);
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

int					update_process(t_pvm *vm, t_process *process)
{
	update_pc(vm, process);
	update_buffer(vm);
	if (!update_memory(vm, process))
		return (0);
	return (1);
}
