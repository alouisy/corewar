/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgroc-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:20:03 by jgroc-de          #+#    #+#             */
/*   Updated: 2018/11/23 18:57:18 by jgroc-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
** aff comme … comme … affooo… non affaaaa… non affuuuuu? non plus. affouuuuuu?!
*/

int	ft_aff(t_pvm *vm, t_list *node)
{
	unsigned char	c;
	t_process		*process;

	process = get_process(node);
	c = 0;
	if (is_reg(vm, 0))
	{
		c = *(reg(process, vm->param[0]));
		if (vm->verbose & 4)
			ft_printf("Aff: %c\n", c);
	}
	update_pc(vm, process, 4, 1);
	return (1);
}
