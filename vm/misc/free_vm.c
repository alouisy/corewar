/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:34:58 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/17 15:35:04 by jgroc-de         ###   ########.fr       */
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
		ft_lstdel(&(vm->trash), 1, &aux_del);
	}
	if (vm->verbose == 1)
	{
		endwin();
	}
}
