/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:34:58 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/27 17:13:35 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	aux_del(void *content)
{
	free(content);
}

void	free_vm(t_pvm *vm)
{
	t_list *node;
	t_list *save;

	vm->c2d = -1;
	cycle2die(vm, 1);
	if (vm->trash)
	{
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
		endwin();
}
