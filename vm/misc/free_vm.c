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

static void	aux_del(void *content, UNUSED size_t size)
{
	free(content);
}

void		free_vm(t_pvm *vm)
{
	ft_lstdel(&(vm->champions), &aux_del);
	ft_lstdel(&(vm->processes), &aux_del);
}
