/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle2die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:26:50 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 19:02:38 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int	decremente_c2d(t_pvm *vm)
{
	int out;

	if (vm->sum_lives >= NBR_LIVE || vm->nb_checks >= MAX_CHECKS)
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

static void	update_state(t_list *node)
{
	(get_process(node))->state = ((get_process(node))->state >> 1) << 1;
}

static void aux_verbose(t_pvm *vm, t_list *node)
{
	if (vm->c2d > 0 && vm->verbose > 1)
	{
		ft_printf("Process %ld hasn't lived for %d cycles (CTD %d)\n",
				node->content_size,
				vm->total_cycles - ((vm->last_live) ? vm->last_live : vm->last_live2),
				vm->c2d);
	}
}

static void	check_process(t_pvm *vm, int mode)
{
	t_list	*node;
	t_list	*save;
	int		i;

	i = 0;
	while (i < 1001)
	{
		node = vm->stack[i].next;
		save = &(vm->stack[i]);
		while (node)
		{
			if ((get_process(node))->state % 2 != 1 || mode)
			{
				vm->nb_process--;
				save->next = node->next;
				node->next = vm->trash;
				vm->trash = node;
				aux_verbose(vm, node);
				node = save;
			}
			else
				update_state((save = node));
			node = node->next;
		}
		vm->stack[i++].content = save;
	}
}

void		cycle2die(t_pvm *vm, int mode)
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
	if (out && vm->c2d > 0)
		ft_printf("Cycle to die is now %d\n", vm->c2d);
}
