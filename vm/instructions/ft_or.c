/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 17:13:08 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/16 18:27:41 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** logical or
** -vm->champions[(int)process->champ_nbr].nbr,
*/

static void	aux_verbose(t_pvm *vm, t_list *node, int val1, int val2)
{
	if ((vm->verbose == 3))
	{
		ft_printf("P% 5d | or %d %d r%d\n",
				node->content_size,
				val1,
				val2,
				vm->param[2]);
	}
}

int			ft_or(t_pvm *vm, t_list *node)
{
	return (aux_andorxor(vm, node, 2, &aux_verbose));
}
