/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouisy- <alouisy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:41:07 by alouisy-          #+#    #+#             */
/*   Updated: 2018/11/16 18:35:26 by jgroc-de         ###   ########.fr       */
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
	t_list	*node;
	t_list	*save;

	modulo = cycles % 1001;
	vm->stack[modulo].content_size = cycles;
	node = (t_list*)(vm->stack[modulo].next);
	save = (vm->stack + modulo);
	while (node && node->content_size > process->content_size)
	{
		save = node;
		node = node->next;
	}
	save->next = process;
	process->next = node;
	if (!node)
		vm->stack[modulo].content = process;
}
