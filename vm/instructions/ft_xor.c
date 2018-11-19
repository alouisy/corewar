/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:13:37 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/17 15:18:29 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** logical XOR
*/

static void	aux_verbose(t_pvm *vm, t_list *node, int val1, int val2)
{
	if (vm->verbose & 4)
	{
		ft_printf("P% 5d | xor %d %d r%d\n",
				node->content_size,
				val1,
				val2,
				vm->param[2]);
	}
}

int			ft_xor(t_pvm *vm, t_list *node)
{
	return (aux_andorxor(vm, node, 3, &aux_verbose));
}
