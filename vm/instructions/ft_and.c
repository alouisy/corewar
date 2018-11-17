/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:11:05 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/17 15:15:56 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** logical and
*/

static void	aux_verbose(t_pvm *vm, t_list *node, int val1, int val2)
{
	if (vm->verbose == 3)
	{
		ft_printf("P% 5d | and %d %d r%d\n",
				node->content_size,
				val1,
				val2,
				vm->param[2]);
	}
}

int			ft_and(t_pvm *vm, t_list *node)
{
	return (aux_andorxor(vm, node, 1, &aux_verbose));
}
