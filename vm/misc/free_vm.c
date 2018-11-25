/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:34:58 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/24 16:14:52 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	aux_del(void *content)
{
	free(content);
}

void	free_vm(t_pvm *vm)
{
	vm->c2d = -1;
	cycle2die(vm, 1);
	if (vm->trash)
	{
		t_list *node;
		t_list *save;

		node = vm->trash;
		while (node)
		{
			save = node->next;
			free(node->content);
			free(node);
			node = save;
		}
	}
	if (vm->nc_mode)
	{
		endwin();
	}
}
