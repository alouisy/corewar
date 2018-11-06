/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:34:58 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/10/26 15:35:00 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static void	aux_del(void *content)
{
	free(content);
}

void		free_vm(t_pvm *vm)
{
	if (vm->champions)
		ft_lstdel(&(vm->champions), 1, &aux_del);
	if (vm->processes)
		ft_lstdel(&(vm->processes), 1, &aux_del);
	if (vm->nc.buffer)
		ft_lstdel(&(vm->nc.buffer), 1, &aux_del);
	if (vm->nc.ncurses)
		close_ncurses(vm);
}
