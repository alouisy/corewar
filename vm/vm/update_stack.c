/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/10/29 19:01:00 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	update_stack(t_pvm *vm, int cycles, t_list *tmp)
{
	t_list *node;

	node = (t_list*)(vm->stack[(cycles) % 1001].content);
	tmp->next = NULL;
	if (node)
		node->next = tmp;
	else
		vm->stack[(cycles) % 1001].next = tmp;
	vm->stack[(cycles) % 1001].content = tmp;
}
