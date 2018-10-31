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
				print_case(vm->nc.wleft, i, i, vm->memory);
			else
			{
				wattron(vm->nc.wleft, COLOR_PAIR((get_buffer(node))->color));
				print_case(vm->nc.wleft, i, i, vm->memory);
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

static inline int	update_memory(t_pvm *vm, t_process *process)
{
	int			i;
	t_list 		*node;
	t_buffer	mem;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->memory[i] != (CHAMPION(process->champ))->memory[i])
		{
			if (vm->memory[i])
			{
				wattron(vm->nc.wleft,
						COLOR_PAIR((CHAMPION(process->champ))->color + 8));
				print_case(vm->nc.wleft, i, i, vm->memory);
				wattroff(vm->nc.wleft,
						COLOR_PAIR((CHAMPION(process->champ))->color + 8));
				mem.i = i;
				mem.color = (CHAMPION(process->champ))->color;
				mem.cycle = 10;
				if (!(node = ft_lstnew(&mem, sizeof(mem))))
					return (0);
				ft_lstadd(&(vm->nc.buffer), node);
				aux_erase(vm, process, i);
			}
			else
				print_case(vm->nc.wleft, i, i, vm->memory);
		}
		i++;
	}
	return (1);
}

static inline void	update_pc(t_pvm *vm, t_process *process)
{
	int	i;

	i = 4;
	if (process->cycle_bf_exe == 1 || process->cycle_bf_exe == 0)
		i = 0;
	wattron(vm->nc.wleft, COLOR_PAIR((CHAMPION(process->champ))->color + i));
	print_case(vm->nc.wleft, process->pc, process->pc, vm->memory);
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
