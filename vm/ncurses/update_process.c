/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:49:38 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/31 17:33:30 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** update process state champion's memory in left panel
*/

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
			if (vm->memory[i] == 0)
				print_case(vm->nc.wleft, i, vm->memory[i]);
			else
			{
				wattron(vm->nc.wleft, COLOR_PAIR((get_buffer(node))->color));
				print_case(vm->nc.wleft, i, vm->memory[i]);
				wattroff(vm->nc.wleft, COLOR_PAIR((get_buffer(node))->color));
			}
			todel = ft_lstpop(node, &(vm->nc.buffer));
		}
		node = node->next;
		if (todel)
		{
			ft_lstdelone(&todel, &ft_del1);
			free(todel);
			todel = NULL;
		}
	}
}

static void	aux_erase(t_pvm *vm, t_process *process, int i)
{
	t_list *node;

	node = vm->champions;
	while (node)
	{
		if (node == process->champ)
			(CHAMPION(process->champ))->memory[i] = vm->memory[i];
		else
			(CHAMPION(node))->memory[i] = 0;
		node = node->next;
	}
}

int					store_buffer(t_pvm *vm, int i, int color, int cycles)
{
	t_list 		*node;
	t_buffer	mem;

	mem.i = i;
	mem.color = color;
	mem.cycle = cycles;
	if (!(node = ft_lstnew(&mem, sizeof(mem))))
		return (0);
	ft_lstadd(&(vm->nc.buffer), node);
	return (1);
}

static inline int	update_memory(t_pvm *vm, t_process *process)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->memory[i] != (CHAMPION(process->champ))->memory[i])
		{
			wattron(vm->nc.wleft,
					COLOR_PAIR((CHAMPION(process->champ))->color + 8));
			print_case(vm->nc.wleft, i, vm->memory[i]);
			wattroff(vm->nc.wleft,
					COLOR_PAIR((CHAMPION(process->champ))->color + 8));
			if (!store_buffer(vm, i, (CHAMPION(process->champ))->color, 10))
				return (0);
			aux_erase(vm, process, i);
		}
		i++;
	}
	return (1);
}

static inline int	update_pc(t_pvm *vm, t_process *process)
{
	int	color;
	int cycles;

	if (process->wait)
	{
		process->wait = 0;
		color = (CHAMPION(process->champ))->color + 4;
		cycles = process->cycle_bf_exe;
		if (vm->memory[process->pc] == 0)
			cycles = 1;
		wattron(vm->nc.wleft, COLOR_PAIR(color));
		print_case(vm->nc.wleft, process->pc, vm->memory[process->pc]);
		if (!store_buffer(vm, process->pc, (CHAMPION(process->champ))->color, cycles))
			return (0);
		wattroff(vm->nc.wleft, COLOR_PAIR(color));
	}
	return (1);
}

int					update_process(t_pvm *vm, t_process *process)
{
	update_buffer(vm);
	update_pc(vm, process);
	if (!update_memory(vm, process))
		return (0);
	return (1);
}
