/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle2die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:26:50 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 17:29:50 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static void	dec_c2d(t_pvm *vm)
{
	if (vm->sum_lives >= NBR_LIVE || vm->nb_checks >= MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nb_checks = 0;
	}
	else
		vm->nb_checks++;
}

void ft_del(UNUSED void *content, UNUSED size_t t)
{
	//free(content);
}

void	cycle2die(t_pvm *vm)
{
	t_list	*node;
	t_list	*save;

	node = vm->processes;
	save = node;
	vm->cur_cycle = 0;
	while (node)
	{
		if ((PROCESS(node))->cycles_wo_live == 0)
		{
			node = ft_lstpop(node, vm->processes);
			ft_lstdelone(&node, &ft_del);
			node = save;
		}
		else
		{
			(PROCESS(node))->cycles_wo_live = 0;
		}
		save = node;
		node = node->next;
	}
	dec_c2d(vm);
}
