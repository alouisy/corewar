/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:46:28 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/18 12:54:21 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int	aux_fork(t_pvm *pvm, t_list *proc, int value)
{
	int			new_pc;
	t_list		*node;
	t_list		*save;
	t_process	*process;

	process = get_process(proc);
	new_pc = (process->pc + value) % MEM_SIZE;
	if (new_pc < 0)
		new_pc += MEM_SIZE;
	if (pvm->trash)
	{
		node = pvm->trash;
		pvm->trash = node->next;
		node->next = NULL;
		*((t_process*)(node->content)) = *process;
	}
	else if (!(node = ft_lstnew2(process, sizeof(t_process))))
		return (0);
	pvm->nb_process++;
	node->content_size = ++pvm->pid;
	new_process_init(process, get_process(node), new_pc);
	save = pvm->stack;
	pvm->stack = node;
	node->next = save;
	return (1);
}
