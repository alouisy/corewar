/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/15 13:21:28 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	aux_fork(t_pvm *pvm, t_process *process, int value)
{
	int			new_pc;
	t_list		*node;

	pvm->nb_process++;
	new_pc = (PC + value) % MEM_SIZE;
	while (new_pc < 0)
		new_pc = (new_pc + MEM_SIZE) % MEM_SIZE;
	if (pvm->trash)
	{
		node = pvm->trash;
		pvm->trash = node->next;
		node->next = NULL;
		*((t_process*)(node->content)) = *process;
	}
	else if (!(node = ft_lstnew2(process, sizeof(t_process))))
		return (0);
	node->content_size = ++pvm->pid;
	new_process_init(process, (PROCESS(node)), new_pc);
	update_stack(pvm, pvm->total_cycles, node);
	return (1);
}
