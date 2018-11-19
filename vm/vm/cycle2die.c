/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle2die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:26:50 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/18 16:40:32 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int		decremente_c2d(t_pvm *vm)
{
	int out;

	if (vm->sum_lives >= NBR_LIVE || vm->nb_checks == MAX_CHECKS - 1)
	{
		vm->c2d -= CYCLE_DELTA;
		vm->nb_checks = 0;
		out = 1;
	}
	else
	{
		vm->nb_checks++;
		out = 0;
	}
	vm->cycle_to_die += vm->c2d;
	vm->sum_lives = 0;
	return (out);
}

static void aux_verbose(t_pvm *vm, t_list *node)
{
	if (vm->verbose & 8 && vm->c2d > 0)
	{
		ft_printf("Process %ld hasn't lived for %d cycles (CTD %d)\n",
				node->content_size,
				vm->total_cycles - (get_process(node))->last_live,
				vm->c2d);
	}
}

static t_list	*delete_process(t_pvm *vm, t_list **save, t_list *node)
{
	aux_verbose(vm, node);
	if (node == vm->stack)
	{
		*save = node->next;
		node->next = vm->trash;
		vm->trash = node;
		vm->stack = *save;
		return (*save);
	}
	else
	{
		(*save)->next = node->next;
		node->next = vm->trash;
		vm->trash = node;
		return ((*save)->next);
	}
}

static void		check_process(t_pvm *vm, int mode)
{
	t_list	*node;
	t_list	*save;

	node = vm->stack;
	save = vm->stack;
	while (node)
	{
		if (!((get_process(node))->state & 1) || mode)
		{
			vm->nb_process--;
			node = delete_process(vm, &save, node);
		}
		else
		{
			(get_process(node))->state &= 2;
			save = node;
			node = node->next;
		}
	}
}

void			cycle2die(t_pvm *vm, int mode)
{
	int i;
	int out;

	check_process(vm, mode);
	out = decremente_c2d(vm);
	i = 0;
	while (i < vm->nb_champ)
	{
		vm->champions[i++].nb_live = 0;
	}
	if (vm->verbose & 8 && out)
		ft_printf("Cycle to die is now %d\n", vm->c2d);
}
