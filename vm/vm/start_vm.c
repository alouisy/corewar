/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/18 16:38:12 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	move_to_trash(t_pvm *vm, t_list *save)
{
	t_list *node;

	node = vm->trash;
	while (node && node->next)
		node = node->next;
	if (!node)
		vm->trash = save;
	else
		node->next = save;
}

int		do_it(t_pvm *vm, t_list *node)
{
	t_list		*save;
	t_process	*content;
	int			cycle;

	while (node)
	{
		save = node->next;
		content = get_process(node);
		if (content->opcode == 0)
			cycle = get_opcode(vm, content);
		else if (content->cycle_of_exe == vm->total_cycles)
			cycle = process_instruction(vm, node);
		if (!cycle)
		{
			move_to_trash(vm, save);
			return (0);
		}
		node = save;
	}
	return (1);
}

int		start_vm(t_pvm *vm)
{
	t_list		*node;

	while (vm->total_cycles != vm->dump && vm->nb_process)
	{
		if (vm->total_cycles >= vm->cycle_to_die)
			cycle2die(vm, 0);
		if (!vm->nb_process)
			break ;
		node = vm->stack;
		vm->total_cycles++;
		if (vm->verbose & 2)
			ft_printf("It is now cycle %d\n", vm->total_cycles);
		if (!do_it(vm, node))
			return (0);
		if (vm->nc_mode)
			status_game(vm);
	}
	if (vm->total_cycles == vm->dump)
		print_memory(vm);
	print_winner(vm);
	return (1);
}
