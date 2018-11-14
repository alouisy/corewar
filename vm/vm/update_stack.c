/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/09 15:54:44 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** stack[i].content contient l'adresse du dernier maillon de la chaine
** pour eviter de parcouir toute la chaine
** stack[i].next démarre la chaine
*/

void	update_stack(t_pvm *vm, int cycles, t_list *process)
{
	int		modulo;
	t_list *node;

	modulo = cycles % 1001;
	vm->stack[modulo].content_size = cycles;
	node = (t_list*)(vm->stack[modulo].content);
	if (node)
	{
		node->next = process;
	}
	else
	{
		vm->stack[modulo].next = process;
	}
	vm->stack[modulo].content = process;
	process->next = NULL;
}
